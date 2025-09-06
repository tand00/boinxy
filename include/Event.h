#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

#define ACTION_NONE -1

enum EventType {
    Pulse,
    NoteOn,
    NoteOff,
};

struct Event {
    EventType type = Pulse;
    int action = ACTION_NONE;
    uint8_t instrument = 0;

    bool operator==(const Event& other) const;
};

#endif