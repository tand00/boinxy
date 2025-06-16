#ifndef BOINX_STATE_H
#define BOINX_STATE_H

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

struct GlobalSettings {
    unsigned int key; // Define chords
    int transpose; // Transposition (white keys mode ?)
};

#endif
