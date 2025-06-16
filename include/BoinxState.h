#ifndef BOINX_STATE_H
#define BOINX_STATE_H

enum InputMode {
    LiveInput,
    SequencerInput,
    EffectInput,
    SettingsInput
};

enum EventType {
    NoteOn,
    NoteOff,
    PlaySample,
    ChordOn,
    ChordOff
};

struct Event {
    EventType type;
    int param;
};

struct BoinxState {
    InputMode mode = LiveInput;
    unsigned int key; // Define chords
    int transpose = 0; // Transposition (white keys mode ?)
};

#endif
