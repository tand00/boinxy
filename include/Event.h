#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

#define ACTION_NONE -1

typedef int16_t action_index;

enum EventType {
    Pulse,
    NoteOn,
    NoteOff,
};

struct Event {
    EventType type = Pulse;
    int16_t action = ACTION_NONE;
    uint8_t instrument = 0;

    bool operator==(const Event& other) const;
    bool isSameAction(const Event& other) const;

    bool isNone() const;
    void nonify();

    Event on() const;
    Event off() const;
    Event pulse() const;

    bool isOn() const;
    bool isOff() const;
    bool isPulse() const;
};

#endif