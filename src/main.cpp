#include <Arduino.h>

#include <Pins.h>

#include <Adafruit_MCP23X17.h>
#include <Adafruit_SH110X.h>
#include <Encoder.h>
#include <USBHost_t36.h>
#include <LedControl.h>

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
Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Encoder encoder1(ENCODER_1_A, ENCODER_1_B);
Encoder encoder2(ENCODER_2_A, ENCODER_2_B);
Encoder encoder3(ENCODER_3_A, ENCODER_3_B);
Encoder encoder4(ENCODER_4_A, ENCODER_4_B);

AudioPlaySdWav* samplePlayers[] = { &sdSamplePlayer1, &sdSamplePlayer2, &sdSamplePlayer3, &sdSamplePlayer4 };

Sequencer sequencer;
Solfagus solfagus;
Instrument* instruments[N_INSTRUMENTS] = {
    new NaiveSynth(),
    new SamplePlayer(samplePlayers, 4)
};

BoinxState state = { LiveInput, 0, instruments, &sequencer, &solfagus };

LivePage livePage(&state);
SequencerPage sequencerPage(&state);

void setup() 
{
    Serial.begin(BAUDRATE);
    Serial.println("[BOINX]");
    Serial.println("Initializing...");
    if(!mcp.begin_I2C()) {
        Serial.println("Unable to initialize MCP !");
    }
    Serial.println("Initialized MCP !");
    if(!display.begin(SCREEN_ADDR)) {
        Serial.println("Unable to initialize display !");
    }
    Serial.println("Initialized Display !");
    for(int i = 0 ; i < leds.getDeviceCount() ; i++) {
        leds.clearDisplay(i);
    }
    Serial.println("Initialized Leds Matrix !");
    Serial.println("Boinx is ready to rock !");
}

void loop() 
{
    sequencer.update();
    switch(state.mode) {
        case LiveInput:
            livePage.update();
            break;
        case SequencerInput:
            sequencerPage.update();
            break;
        default:
            break;
    }
    i2sOutput.update();
}