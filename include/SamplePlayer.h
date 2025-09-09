#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>
#include <Instrument.h>

#define N_PLAYERS 4
#define MAX_SAMPLES 8

class SamplePlayer : public Instrument {

    public:

        SamplePlayer();

        void playSample(int i);
        void playSample(const String& path);
        void playSample(const char* path);

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const String getActionName(int i) const override;

        void registerSample(String path);
        void registerSampleAt(String path, uint8_t i);

        uint8_t channels() const;

        AudioStream& getOutput() override;

    private:

        String _samples[MAX_SAMPLES];
        uint8_t _n_samples = 0;

        AudioPlaySdWav _players[N_PLAYERS];
        AudioMixer4 _sampleMixer;
        uint8_t _player_index = 0;

        // Assuming Mono
        AudioConnection _patchCord1;
        AudioConnection _patchCord2;
        AudioConnection _patchCord3;
        AudioConnection _patchCord4;

};

#endif