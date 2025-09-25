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
        const String getActionName(int16_t i) const override;

        uint8_t getSettingsCount() const override;
        const char* getSettingName(uint8_t i) const override;
        void configureSetting(uint8_t setting, int value) override;
        int getSettingValue(uint8_t i) const override;

        String logSetting(uint8_t i) override;

        void update() override;

        AudioStream& getOutput() override;

    private:

        String _name;

        int voiceIndex(const int note) const;
        int findFreeIndex(const int note) const;

        int16_t _notes[N_SYNTH_VOICES];

        AudioMixer4 _mixer1;
        AudioMixer4 _mixer2;
        AudioMixer4 _finalMixer;
        T _voices[N_SYNTH_VOICES];

        AudioConnection _voicesOut[N_SYNTH_VOICES];
        AudioConnection _mixer1Out;
        AudioConnection _mixer2Out;

        uint8_t _active_voices = 0;

};

extern template class PolySynth<SynthwaveLead>;
extern template class PolySynth<FMSynth>;

#endif