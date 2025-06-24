#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>
#include <Instrument.h>

class SamplePlayer : public Instrument {

    public:

        SamplePlayer(AudioPlaySdWav* players[], const uint8_t n_players);

        void playSample(int i);

        void onEvent(Event ev) override;
        const char* getName() const override; 
        const char* getParamName(int i) const override;

    private:

        AudioPlaySdWav** _players;
        uint8_t _n_players;

};

#endif