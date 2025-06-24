#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "Event.h"

class Instrument {

    public:

        virtual void onEvent(Event) = 0;
        virtual const char* getName() const = 0; 
        virtual const char* getParamName(int i) const = 0;

};

#endif
