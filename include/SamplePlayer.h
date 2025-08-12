#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>
#include <Instrument.h>

#define N_PLAYERS 4

class SamplePlayer : public Instrument {

    public:

        SamplePlayer();

        void playSample(int i);

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const char* getActionName(int i) const override;

        AudioStream& getOutput() override;

    private:

        AudioPlaySdWav _players[N_PLAYERS];
        AudioMixer4 _sampleMixer;

        // Assuming Mono
        AudioConnection _patchCord1;
        AudioConnection _patchCord2;
        AudioConnection _patchCord3;
        AudioConnection _patchCord4;

};

#endif