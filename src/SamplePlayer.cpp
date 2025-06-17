#include <SamplePlayer.h>

SamplePlayer::SamplePlayer(AudioPlaySdWav *players[], const size_t n_players)
    : _players(players), _n_players(n_players)
{

}

const char *SamplePlayer::getSampleName(int i)
{
    return "samples/0.wav";
}

void SamplePlayer::playSample(int i)
{
    const char* filename = getSampleName(i);
    size_t selected = 0;
    uint32_t max_pos = 0;
    for(size_t i = 0 ; i < _n_players ; i++) {
        if(!_players[i]->isPlaying()) {
            selected = i;
            break;
        } else {
            uint32_t pos = _players[i]->positionMillis();
            if(pos > max_pos) {
                max_pos = pos;
                selected = i;
            }
        }
    }
    _players[selected]->play(filename);
}
