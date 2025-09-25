#ifndef SYNTHWAVE_LEAD_H
#define SYNTHWAVE_LEAD_H

#include <Arduino.h>
#include <Audio.h>
#include <Instrument.h>

class SynthwaveLead : public Instrument {

    public:

        SynthwaveLead();

        void onEvent(Event) override;
        const char* getName() const override;
        const String getActionName(int16_t i) const override;

        uint8_t getSettingsCount() const override;
        const char* getSettingName(uint8_t i) const override;
        void configureSetting(uint8_t setting, int value) override;
        int getSettingValue(uint8_t i) const override;

        String logSetting(uint8_t i) override;

        void update() override;

        AudioStream& getOutput() override;

        void setNote(int8_t note);

    private:

        int _detune = 10;
        int _low_pass = 100;
        int _volume = 20;
        int _sustain = 80;
        int _n_osc = 3;
        int _crusher_bits = 16;
        int _crusher_freq = 100;

        int8_t _note = 0;

        AudioSynthWaveform _osc1;
        AudioSynthWaveform _osc2;
        AudioSynthWaveform _osc3;
        AudioMixer4 _mixer;
        AudioEffectEnvelope _envelope;
        AudioFilterStateVariable _filter;
        AudioEffectBitcrusher _crusher;
        AudioAmplifier _amp;

        AudioConnection _osc1Out;
        AudioConnection _osc2Out;
        AudioConnection _osc3Out;
        AudioConnection _mixerOut;
        AudioConnection _envelopeOut;
        AudioConnection _filterOut;
        AudioConnection _crusherOut;

};

#endif