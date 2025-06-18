#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>

class SamplePlayer {

    public:

        SamplePlayer(AudioPlaySdWav* players[], const uint8_t n_players);

        const char* getSampleName(int i);
        void playSample(int i);

    private:

        AudioPlaySdWav** _players;
        uint8_t _n_players;

};

#endif