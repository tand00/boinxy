#include <Arduino.h>

#include <Pins.h>

#include <Adafruit_MCP23X17.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <USBHost_t36.h>
#include <LedControl.h>
#include <Bounce.h>

#include <Screen.h>
#include <Keyboard.h>
#include <BoinxState.h>
#include <BoinxAudio.h>
#include <Button.h>
#include <AppPage.h>
#include <Sequencer.h>
#include <Solfagus.h>

#include <Instrument.h>
#include <SamplePlayer.h>
#include <NaiveSynth.h>

#include <LivePage.h>
#include <SequencerPage.h>

USBHost usb_host;
MIDIDevice midi_in(usb_host);

LedControl leds(MATRIX_DATA, MATRIX_CLK, MATRIX_CS, MATRIX_COUNT);
Adafruit_MCP23X17 mcp;
Encoder encoder1(ENCODER_1_A, ENCODER_1_B);
Encoder encoder2(ENCODER_2_A, ENCODER_2_B);
Encoder encoder3(ENCODER_3_A, ENCODER_3_B);
Encoder encoder4(ENCODER_4_A, ENCODER_4_B);
Bounce encoder1Btn(ENCODER_1_S, 10);
Bounce encoder2Btn(ENCODER_2_S, 10);
Bounce encoder3Btn(ENCODER_3_S, 10);
Bounce encoder4Btn(ENCODER_4_S, 10);
Bounce btnAlter(ALTER_BUTTON, 10);
Bounce btnRecord(RECORD_BUTTON, 10);
Bounce btn2(BUTTON_2, 10);
Bounce btn3(BUTTON_3, 10);

//AudioPlaySdWav* samplePlayers[] = { &sdSamplePlayer1, &sdSamplePlayer2, &sdSamplePlayer3, &sdSamplePlayer4 };
Screen screen;
Sequencer sequencer;
Keyboard keyboard;
Solfagus solfagus;
Instrument* instruments[N_INSTRUMENTS] = {
    new NaiveSynth(),
    //new SamplePlayer(samplePlayers, 4)
};

BoinxState state = { LiveInput, 0, instruments, &sequencer, &solfagus, false };

LivePage livePage(&state);
SequencerPage sequencerPage(&state);

void setup() 
{
    Wire.begin();
    Serial.begin(BAUDRATE);
    Serial.println("[BOINX]");
    Serial.println("Initializing...");
    keyboard.setup();
    screen.setup();
    for(int i = 0 ; i < leds.getDeviceCount() ; i++) {
        leds.shutdown(i, false);
        leds.clearDisplay(i);
    }
    Serial.println("Initialized Leds Matrix !");
    
    pinMode(ENCODER_1_S, INPUT_PULLUP);
    pinMode(ENCODER_2_S, INPUT_PULLUP);
    pinMode(ENCODER_3_S, INPUT_PULLUP);
    pinMode(ENCODER_4_S, INPUT_PULLUP);
    pinMode(ALTER_BUTTON, INPUT_PULLUP);
    pinMode(RECORD_BUTTON, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("Boinx is ready to rock !");
}

void updateMatrixSequencerDisplay() {
    if(sequencer.step_flag) {
        int step = sequencer.getCurrentStep();
        int matrix = step / 8;
        int col = 7 - (step % 8);
        for(int i = 0 ; i < leds.getDeviceCount() ; i++) {
            leds.setIntensity(i, sequencer.pulse_flag ? 8 : 0);
            leds.clearDisplay(i);
        }
        leds.setLed(matrix, 7, col, true);
    }
}

void updateSequencerControl() {
    sequencer.update();
    if(encoder1Btn.update() && encoder1Btn.fallingEdge()) {
        screen.message("Play/Pause");
        sequencer.playPause();
    }
    int encoderDelta = state.alter ? encoder1.read() : (encoder1.read() / 4);
    if(encoderDelta != 0) {
        sequencer.setTempo(sequencer.getTempo() + encoderDelta);
        encoder1.write(0);
        screen.message(String("New tempo : ") + sequencer.getTempo());
    }
}

void loop() 
{
    if(btnAlter.update()) {
        state.alter = btnAlter.fallingEdge();
    }
    updateSequencerControl();
    updateMatrixSequencerDisplay();
    screen.update(&state);
    /*
    switch(state.mode) {
        case LiveInput:
            livePage.update();
            break;
        case SequencerInput:
            sequencerPage.update();
            break;
        default:
            break;
    }*/
}