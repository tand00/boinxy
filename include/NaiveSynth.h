#ifndef NAIVE_SYNTH_H
#define NAIVE_SYNTH_H

#include <Instrument.h>

class NaiveSynth : public Instrument {

    public:

        NaiveSynth();

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const char* getParamName(int i) const override;

    private:

};

#endif