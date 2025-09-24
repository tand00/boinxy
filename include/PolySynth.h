#ifndef POLY_SYNTH_H
#define POLY_SYNTH_H

#include <Arduino.h>
#include <Audio.h>
#include <Instrument.h>

#include <SynthwaveLead.h>
#include <FMSynth.h>

#define N_SYNTH_VOICES 8

template<class T>
class PolySynth : public Instrument {

    public:

        PolySynth(String name);

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

        String _name;

        int voiceIndex(const int note) const;
        int findFreeIndex(const int note) const;

        int _notes[N_SYNTH_VOICES];

        AudioMixer4 _mixer1;
        AudioMixer4 _mixer2;
        AudioMixer4 _finalMixer;
        T _voices[N_SYNTH_VOICES];

        AudioConnection _voicesOut[N_SYNTH_VOICES];
        AudioConnection _mixer1Out;
        AudioConnection _mixer2Out;

        int _active_voices = 0;

};

extern template class PolySynth<SynthwaveLead>;
extern template class PolySynth<FMSynth>;

#endif