#include <SamplePlayer.h>

SamplePlayer::SamplePlayer(AudioPlaySdWav *players[], const uint8_t n_players)
    : _players(players), _n_players(n_players)
{

}

void SamplePlayer::playSample(int i)
{
    const char* filename = getParamName(i);
    uint8_t selected = 0;
    uint32_t max_pos = 0;
    for(uint8_t i = 0 ; i < _n_players ; i++) {
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

void SamplePlayer::onEvent(Event ev)
{
    if(ev.type != Pulse) return;
    playSample(ev.param);
}

const char *SamplePlayer::getName() const
{
    return "Sampler";
}

const char *SamplePlayer::getParamName(int i) const
{
    return "samples/000.wav";
}
