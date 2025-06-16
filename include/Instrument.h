#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "BoinxState.h"

class Instrument {
    public:
        virtual Event on_event(Event) = 0;
        virtual char* get_name() const = 0; 
};

#endif
