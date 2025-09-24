#ifndef NAIVE_SYNTH_H
#define NAIVE_SYNTH_H

#include <Instrument.h>
#include <Audio.h>

#include <SynthBlocks.h>

#define N_NAIVE_VOICES 8

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

        short mappedShape() const;

        AudioSynthWaveform _waves[N_NAIVE_VOICES];
        AudioEffectEnvelope _envelopes[N_NAIVE_VOICES];
        AudioConnection _connections[N_NAIVE_VOICES * 2];
        AudioMixer4 _mixer1;
        AudioMixer4 _mixer2;
        AudioMixer4 _finalMixer;
        AudioAmplifier _amp;
        AudioFilterStateVariable _filter;

        AudioConnection _mixer1Out;
        AudioConnection _mixer2Out;
        AudioConnection _finalMixerOut;
        AudioConnection _ampOut;

        int _voices[N_NAIVE_VOICES];

        int _active_voices = 0;

        short _shape = 0;
        int _volume = 20;
        int _low_pass = 50;
        int _duty = 50;

};

#endif