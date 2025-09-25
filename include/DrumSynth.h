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
        const String getActionName(int16_t i) const override;

        uint8_t getSettingsCount() const override;;
        const char* getSettingName(uint8_t i) const override;
        void configureSetting(uint8_t setting, int value) override;
        int getSettingValue(uint8_t i) const override;

        AudioStream& getOutput() override;

    private:

        AudioSynthSimpleDrum _drumSynth;

};

#endif