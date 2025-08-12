#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

enum EventType {
    Pulse,
    NoteOn,
    NoteOff,
};

struct Event {
    EventType type;
    int action;
    uint8_t instrument;
};

#endif