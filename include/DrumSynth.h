#ifndef DRUM_SYNTH_H
#define DRUM_SYNTH_H

#include <Arduino.h>
#include <Audio.h>
#include <Instrument.h>

class DrumSynth : public Instrument {

    public:

        DrumSynth();

        void onEvent(Event) override;
        const char* getName() const override;
        const char* getActionName(int i) const override;

        AudioStream& getOutput() override;

    private:

        AudioSynthSimpleDrum _drumSynth;

};

#endif