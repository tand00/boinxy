#ifndef BOINX_STATE_H
#define BOINX_STATE_H

#include <Instrument.h>
#include <Sequencer.h>
#include <Solfagus.h>
#include <Event.h>

#include <JoyStick.h>
#include <Keyboard.h>

#define N_INSTRUMENTS 2
#define N_PAGES 2

#define NAIVE_SYNTH_I 0
#define SAMPLE_PLAYER_I 1

#define LIVE_PAGE_I 0
#define SEQUENCER_PAGE_I 1

class Screen;
class AppPage;

struct BoinxState {
    AppPage** pages;
    uint8_t page_index = 0;
    Instrument** instruments;
    Sequencer* sequencer;
    Solfagus* solfagus;
    JoyStick* joystick;
    Keyboard* keyboard;
    Screen* screen;
    bool alter = false;

    void execute(Event e) const;
    bool has_changed(const BoinxState& other) const;

    AppPage* page();
    void nextPage();

    void update();
};

#endif
