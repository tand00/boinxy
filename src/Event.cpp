#include "Event.h"

bool Event::operator==(const Event &other) const
{
    return (type == other.type) 
        && (action == other.action) 
        && (instrument == other.instrument);
}
