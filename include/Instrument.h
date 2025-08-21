#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "Event.h"
#include <Audio.h>

class Instrument {

    public:

        virtual void onEvent(Event) = 0;
        virtual const char* getName() const = 0; 
        virtual const char* getActionName(int i) const = 0;

        virtual void update() { }

        virtual AudioStream& getOutput() = 0;

};

#endif
