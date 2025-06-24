#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

enum EventType {
    NoteOn,
    NoteOff,
    Pulse,
};

struct Event {
    EventType type;
    int param;
    uint8_t instrument;
};

#endif