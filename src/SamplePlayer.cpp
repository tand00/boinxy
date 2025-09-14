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
    if(_n_samples <= i) return;
    playSample(getActionName(i).c_str());
}

void SamplePlayer::playSample(const String &path)
{
    playSample(path.c_str());
}

void SamplePlayer::playSample(const char *path)
{
    if(strlen(path) == 0) return;
    uint8_t selected = _player_index;
    _player_index = (_player_index + 1) % N_PLAYERS;
    // for(int i = 0 ; i < N_PLAYERS ; i++) {
    //     if(_players[selected].isPlaying()) {
    //         selected = _player_index;
    //         _player_index = (_player_index + 1) % N_PLAYERS;
    //     }
    // }
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

const String SamplePlayer::getActionName(int i) const
{
    return _samples[i % _n_samples];
}

void SamplePlayer::registerSample(String path)
{
    if(_n_samples == MAX_SAMPLES) return;
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
