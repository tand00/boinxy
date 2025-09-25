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
        const String getActionName(int16_t i) const override;

        AudioStream& getOutput() override;

        uint8_t getSettingsCount() const override;
        const char* getSettingName(uint8_t i) const override;
        void configureSetting(uint8_t setting, int value) override;
        int getSettingValue(uint8_t i) const override;

        void update() override;

        String logSetting(uint8_t i) override;

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

        int16_t _voices[N_NAIVE_VOICES];

        uint8_t _active_voices = 0;

        short _shape = 0;
        int _volume = 20;
        int _low_pass = 50;
        int _duty = 50;

};

#endif