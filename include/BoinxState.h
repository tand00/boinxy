#ifndef BOINX_STATE_H
#define BOINX_STATE_H

#include <Instrument.h>
#include <Sequencer.h>
#include <Solfagus.h>
#include <Event.h>

#include <JoyStick.h>
#include <Keyboard.h>

#include <Encoder.h>
#include <Bounce.h>

// INSTRUMENTS CONSTANTS
#define N_INSTRUMENTS 4

#define NAIVE_SYNTH_I 0
#define SYNTHWAVE_POLY_I 1
#define DRUM_SYNTH_I 2
#define SAMPLE_PLAYER_I 3

// PAGES CONSTANTS
#define N_PAGES 3

#define LIVE_PAGE_I 0
#define SEQUENCER_PAGE_I 1
#define HARMONICA_PAGE_I 2

class Screen;
class AppPage;

struct FrontPanel {
    Encoder encoder1;
    Bounce encoder1Btn;
    Encoder encoder2;
    Bounce encoder2Btn;
    Encoder encoder3;
    Bounce encoder3Btn;
    Bounce button2;
    Bounce button3;

    void update();
};

struct BoinxState {
    AppPage** pages;
    uint8_t page_index = 0;
    Instrument** instruments;
    Sequencer* sequencer;
    Solfagus* solfagus;
    JoyStick* joystick;
    Keyboard* keyboard;
    Screen* screen;
    FrontPanel* panel;
    bool alter = false;
    bool change_signal = false;

    void execute(Event e) const;
    bool has_changed(const BoinxState& other) const;

    AppPage* page();
    void nextPage();

    void setup();
    void update();
};

#endif
