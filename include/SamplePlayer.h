#ifndef BNX_SAMPLE_PLAYER_H
#define BNX_SAMPLE_PLAYER_H

#include <Audio.h>
#include <Instrument.h>

class SamplePlayer : public Instrument {

    public:

        SamplePlayer(AudioPlaySdWav* players[], const uint8_t n_players);

        const char* getSampleName(int i);
        void playSample(int i);

        void on_event(Event ev) override;
        const char* get_name() const override; 

    private:

        AudioPlaySdWav** _players;
        uint8_t _n_players;

};

#endif