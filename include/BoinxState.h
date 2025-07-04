#ifndef BOINX_STATE_H
#define BOINX_STATE_H

#include <Instrument.h>
#include <Sequencer.h>
#include <Solfagus.h>
#include <Event.h>

#define N_INSTRUMENTS 2

enum InputMode {
    LiveInput,
    SequencerInput,
    HarmonicaInput,
    //ThereminInput,
    EffectInput,
    SettingsInput
};

struct BoinxState {
    InputMode mode = LiveInput;
    int transpose = 0;
    Instrument** instruments;
    Sequencer* sequencer;
    Solfagus* solfagus;

    void execute(Event e) const;
};

#endif
