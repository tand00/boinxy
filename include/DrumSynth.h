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
        const String getActionName(int i) const override;

        int getSettingsCount() const override;;
        const char* getSettingName(int i) const override;
        void configureSetting(int setting, int value) override;
        int getSettingValue(int i) const override;

        AudioStream& getOutput() override;

    private:

        AudioSynthSimpleDrum _drumSynth;

};

#endif