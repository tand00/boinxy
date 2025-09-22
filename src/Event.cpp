#include "Event.h"

bool Event::operator==(const Event &other) const
{
    return (type == other.type) 
        && (action == other.action) 
        && (instrument == other.instrument);
}

bool Event::isSameAction(const Event &other) const
{
    return (action == other.action)
        && (instrument == other.instrument);
}

bool Event::isNone() const
{
    return action == ACTION_NONE;
}

void Event::nonify()
{
    action = ACTION_NONE;
}

Event Event::on() const
{
    Event res = *this;
    res.type = NoteOn;
    return res;
}

Event Event::off() const
{
    Event res = *this;
    res.type = NoteOff;
    return res;
}

Event Event::pulse() const
{
    Event res = *this;
    res.type = Pulse;
    return res;
}

bool Event::isOn() const
{
    return type == NoteOn;
}

bool Event::isOff() const
{
    return type == NoteOff;
}

bool Event::isPulse() const
{
    return type == Pulse;
}
