#ifndef NAIVE_SYNTH_H
#define NAIVE_SYNTH_H

#include <Instrument.h>
#include <Audio.h>

class NaiveSynth : public Instrument {

    public:

        NaiveSynth();

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const String getActionName(int i) const override;

        AudioStream& getOutput() override;

    private:

        AudioSynthWaveform _wave1;
        AudioSynthWaveform _wave2;
        AudioSynthWaveform _wave3;
        AudioEffectEnvelope _finalEnvelope;
        AudioAmplifier _amp;

};

#endif