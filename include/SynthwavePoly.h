#ifndef SYNTHWAVE_POLY_H
#define SYNTHWAVE_POLY_H

#include <Arduino.h>
#include <Audio.h>
#include <Instrument.h>
#include <SynthwaveLead.h>

#define N_SYNTH_VOICES 8

class SynthwavePoly : public Instrument {

    public:

        SynthwavePoly();

        void onEvent(Event) override;
        const char* getName() const override;
        const String getActionName(int i) const override;

        int getSettingsCount() const override;
        const char* getSettingName(int i) const override;
        void configureSetting(int setting, int value) override;
        int getSettingValue(int i) const override;

        String logSetting(int i) override;

        void update() override;

        AudioStream& getOutput() override;

    private:

        int voiceIndex(const int note) const;
        int findFreeIndex(const int note) const;

        int _notes[N_SYNTH_VOICES];

        AudioMixer4 _mixer1;
        AudioMixer4 _mixer2;
        AudioMixer4 _finalMixer;
        SynthwaveLead _voices[N_SYNTH_VOICES];

        AudioConnection _voicesOut[N_SYNTH_VOICES];
        AudioConnection _mixer1Out;
        AudioConnection _mixer2Out;

        int _active_voices = 0;

};

#endif