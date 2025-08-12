#include <SamplePlayer.h>

SamplePlayer::SamplePlayer()
{
    _patchCord1.connect(_players[0], 0, _sampleMixer, 0);
    _patchCord2.connect(_players[1], 0, _sampleMixer, 1);
    _patchCord3.connect(_players[2], 0, _sampleMixer, 2);
    _patchCord4.connect(_players[3], 0, _sampleMixer, 3);
}

void SamplePlayer::playSample(int i)
{
    const char* filename = getActionName(i);
    uint8_t selected = 0;
    uint32_t max_pos = 0;
    for(uint8_t i = 0 ; i < N_PLAYERS ; i++) {
        if(!_players[i].isPlaying()) {
            selected = i;
            break;
        } else {
            uint32_t pos = _players[i].positionMillis();
            if(pos > max_pos) {
                max_pos = pos;
                selected = i;
            }
        }
    }
    _players[selected].play(filename);
}

void SamplePlayer::onEvent(Event ev)
{
    if(ev.type != Pulse) return;
    playSample(ev.action);
}

const char* SamplePlayer::getName() const
{
    return "Sampler";
}

const char* SamplePlayer::getActionName(int i) const
{
    return "samples/000.wav";
}

AudioStream& SamplePlayer::getOutput()
{
    return _sampleMixer;
}
