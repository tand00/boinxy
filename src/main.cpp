#include <Arduino.h>

#include <Pins.h>
#include <Settings.h>

// Libraries
#include <Adafruit_MCP23X17.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <USBHost_t36.h>
#include <LedControl.h>
#include <Bounce.h>
#include <EEPROM.h>

// Peripherals
#include <Screen.h>
#include <Keyboard.h>
#include <BoinxState.h>
#include <BoinxAudio.h>
#include <Button.h>
#include <JoyStick.h>

// Models
#include <AppPage.h>
#include <Sequencer.h>
#include <Solfagus.h>
#include <SampleLibrary.h>

// Instruments
#include <Instrument.h>
#include <SamplePlayer.h>
#include <NaiveSynth.h>
#include <DrumSynth.h>
#include <SynthwaveLead.h>

// Pages
#include <LivePage.h>
#include <SequencerPage.h>
#include <HarmonicaPage.h>

// USB MIDI
USBHost usb_host;
MIDIDevice midi_in(usb_host);

// Electronic drivers
LedControl leds(MATRIX_DATA, MATRIX_CLK, MATRIX_CS, MATRIX_COUNT);
Adafruit_MCP23X17 mcp;

// Inputs managed by global logic
Encoder encoder1(ENCODER_1_A, ENCODER_1_B);
Bounce encoder1Btn(ENCODER_1_S, 10);
Bounce btnAlter(ALTER_BUTTON, 10);
Bounce btnChange(BUTTON_3, 10);

// Inputs with page-specific behavior
FrontPanel panel {
    Encoder(ENCODER_2_A, ENCODER_2_B),
    Bounce(ENCODER_2_S, 10),
    Encoder(ENCODER_3_A, ENCODER_3_B),
    Bounce(ENCODER_3_S, 10),
    Encoder(ENCODER_4_A, ENCODER_4_B),
    Bounce(ENCODER_4_S, 10),
    Bounce(BUTTON_1, 10),
    Bounce(BUTTON_2, 10)
};

// Interfaces
Sequencer sequencer;
Keyboard keyboard;
JoyStick joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_S);
Screen screen;
SampleLibrary samples;

// Models
Solfagus solfagus;

// Instruments
SamplePlayer player;
NaiveSynth naiveSynth;
DrumSynth drumSynth;
SynthwaveLead synthLead;

Instrument* instruments[N_INSTRUMENTS] = {
    &naiveSynth, &player, &drumSynth, &synthLead
};
AudioConnection naiveSynthOut;
AudioConnection sampleOut;
AudioConnection drumSynthOut;
AudioConnection synthLeadOut;

// App pages
LivePage livePage;
SequencerPage sequencerPage(&player, &samples);
HarmonicaPage harmonicaPage;
AppPage* pages[N_PAGES] = {&livePage, &sequencerPage, &harmonicaPage};

// State
BoinxState state = {
    pages, 0, 
    instruments, 
    &sequencer, 
    &solfagus, 
    &joystick, 
    &keyboard, 
    &screen, 
    &panel 
};

uint8_t volume = 100;

void midiNoteOn(byte channel, byte note, byte velocity) {
    livePage.noteOn(note, &state);
}
void midiNoteOff(byte channel, byte note, byte velocity) {
    livePage.noteOff(note, &state);
}

void setup() 
{
    Wire.begin();
    Serial.begin(BAUDRATE);
    Serial.println("[BOINX]");
    Serial.println("Initializing...");
    state.setup();
    samples.setup();
    for(int i = 0 ; i < leds.getDeviceCount() ; i++) {
        leds.shutdown(i, false);
        leds.setIntensity(i, 0);
        leds.clearDisplay(i);
    }
    Serial.println("Initialized Leds Matrix !");
    
    pinMode(ENCODER_1_S, INPUT_PULLUP);
    pinMode(ENCODER_2_S, INPUT_PULLUP);
    pinMode(ENCODER_3_S, INPUT_PULLUP);
    pinMode(ENCODER_4_S, INPUT_PULLUP);
    pinMode(ALTER_BUTTON, INPUT_PULLUP);
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    state.page_index = (EEPROM.read(SETTING_PAGE) % N_PAGES);
    state.page()->enter(&state);

    Serial.println("Boinx is ready to rock !");

    sampleOut.connect(player.getOutput(), 0, outMixer, 1);
    naiveSynthOut.connect(naiveSynth.getOutput(), 0, synthMixer, 0);
    drumSynthOut.connect(drumSynth.getOutput(), 0, synthMixer, 1);
    synthLeadOut.connect(synthLead.getOutput(), 0, synthMixer, 2);

    globalVolume.gain(volume / 100.0);

    usb_host.begin();
    midi_in.setHandleNoteOn(midiNoteOn);
    midi_in.setHandleNoteOff(midiNoteOff);

    AudioMemory(64);
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
}

void updateMatrixSequencerDisplay() {
    if(sequencer.step_flag || sequencerPage.update_led) {
        int step = sequencer.getCurrentStep();
        int matrix = step / 8;
        int col = 7 - (step % 8);
        for(int i = 0 ; i < leds.getDeviceCount() ; i++) {
            leds.clearDisplay(i);
            // Disabled because caused sound interferences
            // leds.setIntensity(i, sequencer.pulse_flag ? 4 : 0);
        }
        if(state.page_index == SEQUENCER_PAGE_I) {
            for(int i = 0 ; i < sequencerPage.selection_len ; i++) {
                leds.setRow(i + sequencerPage.selected, sequencerPage.channel, 0b11111111);
            }
        }
        for(int e_step = 0 ; e_step < sequencer.getTrackLen() ; e_step++) {
            uint8_t n_events = sequencer.getEventsCount(e_step);
            Event* events = sequencer.getEvents(e_step);
            for(uint8_t e_i = 0 ; e_i < n_events ; e_i++) {
                if(
                    events[e_i].instrument == SAMPLE_PLAYER_I &&
                    events[e_i].type == Pulse
                ) {
                    int led = events[e_i].action;
                    leds.setLed(e_step / 8, led, 7 - (e_step % 8), true);
                }
            }
        }
        leds.setColumn(matrix, col, 0b11111111);
    }
}

void updateSequencerControl() {
    sequencer.update();
    if(encoder1Btn.update() && encoder1Btn.fallingEdge()) {
        if(state.alter) {
            screen.message("Reset step");
            sequencer.reset();
        } else {
            screen.message("Play/Pause");
            sequencer.playPause();
        }
    }
    int encoderDelta = encoder1.read() / 4;
    if(encoderDelta != 0 && !state.alter) {
        sequencer.setTempo(sequencer.getTempo() + encoderDelta);
        encoder1.write(0);
        screen.message(String("Tempo : ") + sequencer.getTempo());
    } else if(encoderDelta != 0 && state.alter) {
        volume += encoderDelta;
        globalVolume.gain(volume / 100.0);
        encoder1.write(0);
        screen.message(String("Volume : ") + volume);
    }
}

void loop() 
{
    if(btnAlter.update()) {
        state.alter = btnAlter.fallingEdge();
    }
    state.change_signal = false;
    if(btnChange.update()) {
        state.change_signal = btnChange.fallingEdge();
        if(state.alter && state.change_signal) {
            state.change_signal = false;
            state.nextPage();
            EEPROM.write(SETTING_PAGE, state.page_index);
        }
    }
    updateSequencerControl();
    updateMatrixSequencerDisplay();

    if(sequencer.sequence_flag) {
        Serial.println(String("Max usage : ") + AudioMemoryUsageMax());
        Serial.println(String("Max proc : ") + AudioProcessorUsageMax());
        AudioProcessorUsageMaxReset();
        AudioMemoryUsageMaxReset();
    }
    
    midi_in.read();
    state.update();
}