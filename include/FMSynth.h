#ifndef FM_SYNTH_H
#define FM_SYNTH_H

#include <Arduino.h>
#include <Audio.h>
#include <Instrument.h>

class FMSynth : public Instrument {

    public:

        FMSynth();

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

        int _note = 0;

        AudioSynthWaveformModulated _carrier;
        AudioSynthWaveform _modulator;

        AudioEffectEnvelope _modulationEnvelope;
        AudioEffectEnvelope _envelope;

        AudioAmplifier _amp;

        AudioConnection _modulatorOut;
        AudioConnection _modulationEnvelopeOut;
        AudioConnection _carrierOut;
        AudioConnection _envelopeOut;

};

#endif