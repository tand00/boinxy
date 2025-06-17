#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>

class SamplePlayer {

    public:

        SamplePlayer(AudioPlaySdWav* players[], const size_t n_players);

        const char* getSampleName(int i);
        void playSample(int i);

    private:

        AudioPlaySdWav** _players;
        size_t _n_players;

};

#endif