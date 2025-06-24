#ifndef BOINX_STATE_H
#define BOINX_STATE_H

#include <Instrument.h>
#include <Sequencer.h>
#include <Solfagus.h>

enum InputMode {
    LiveInput,
    SequencerInput,
    Harmonica,
    Theremin,
    EffectInput,
    SettingsInput
};

struct BoinxState {
    InputMode mode = LiveInput;
    int transpose = 0; // Transposition (white keys mode ?)
    Instrument** instruments;
    Sequencer* sequencer;
    Solfagus* solfagus;
};

#endif
