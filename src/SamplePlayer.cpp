#include <SamplePlayer.h>

AudioSynthSimpleDrum drumSynth;

SamplePlayer::SamplePlayer()
{
    _patchCord1.connect(_players[0], 0, _sampleMixer, 0);
    _patchCord2.connect(_players[1], 0, _sampleMixer, 1);
    _patchCord3.connect(_players[2], 0, _sampleMixer, 2);
    _patchCord4.connect(_players[3], 0, _sampleMixer, 3);
}

void SamplePlayer::playSample(int i)
{
    if(_n_samples == 0) return;
    const char* filename = getActionName(i);
    playSample(filename);
}

void SamplePlayer::playSample(const String &path)
{
    playSample(path.c_str());
}

void SamplePlayer::playSample(const char *path)
{
    if(strlen(path) == 0) return;
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
    _players[selected].play(path);
}

void SamplePlayer::onEvent(Event ev)
{
    if(ev.type == NoteOff) return;
    playSample(ev.action);
}

const char* SamplePlayer::getName() const
{
    return "Sampler";
}

const char* SamplePlayer::getActionName(int i) const
{
    return _samples[i % _n_samples].c_str();
}

void SamplePlayer::registerSample(String path)
{
    _samples[_n_samples] = path;
    _n_samples = (_n_samples + 1) % MAX_SAMPLES;
}

void SamplePlayer::registerSampleAt(String path, uint8_t i)
{
    _samples[i % MAX_SAMPLES] = path;
}

uint8_t SamplePlayer::channels() const
{
    return _n_samples;
}

AudioStream& SamplePlayer::getOutput()
{
    return _sampleMixer;
}
