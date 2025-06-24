#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "Event.h"

class Instrument {

    public:

        virtual void on_event(Event) = 0;
        virtual const char* get_name() const = 0; 

};

#endif
