#ifndef NAIVE_SYNTH_H
#define NAIVE_SYNTH_H

#include <Instrument.h>
#include <Audio.h>

#include <SynthBlocks.h>

#define N_VOICES 8
#define N_VOICES_MIXERS (N_VOICES / 4) + ((N_VOICES % 4 == 0) ? 0 : 1)

class NaiveSynth : public Instrument {

    public:

        NaiveSynth();

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const String getActionName(int i) const override;

        AudioStream& getOutput() override;

        int getSettingsCount() const override;
        const char* getSettingName(int i) const override;
        void configureSetting(int setting, int value) override;
        int getSettingValue(int i) const override;

        void update() override;

        String logSetting(int i) override;

    private:

        int voiceIndex(const int note) const;
        int findFreeIndex(const int note) const;

        short mappedShape() const { return _shape; }

        AudioSynthWaveform _waves[N_VOICES];
        AudioEffectEnvelope _envelopes[N_VOICES];
        AudioConnection _connections[N_VOICES * 2];
        AudioMixer4 _mixer1;
        AudioMixer4 _mixer2;
        AudioMixer4 _finalMixer;
        AudioFilterBiquad _filter;
        AudioEffectFreeverb _reverb;
        AudioAmplifier _amp;

        AudioConnection _mixer1Out;
        AudioConnection _mixer2Out;
        AudioConnection _finalMixerOut;
        AudioConnection _filterOut;
        AudioConnection _reverbOut;

        int _voices[N_VOICES] = { -1 };

        int _active_voices = 0;

        short _shape = 0;
        int _volume = 100;
        int _low_pass = 50;
        int _reverb_amount = 0.0; 

};

#endif