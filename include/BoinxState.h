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
#define N_INSTRUMENTS 5

// PAGES CONSTANTS
#define N_PAGES 3

#define LIVE_PAGE_I 0
#define SEQUENCER_PAGE_I 1
#define HARMONICA_PAGE_I 2

#define ENCODERS_MIN_STEPS 4

#define MAX_TRACKS 16

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
    
    int16_t tracks_instruments[MAX_TRACKS];
    Event active_events[MAX_ACTIVE_EVENTS];

    void execute(Event e);
    void flush();
    void flushInstrument(int instru);

    bool has_changed(const BoinxState& other) const;

    AppPage* page();
    void nextPage();

    void setup();
    void update();

    private:

        bool updateActiveEvents(Event e);
};

#endif
