#include <SynthwavePoly.h>

SynthwavePoly::SynthwavePoly()
{
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        _notes[i] = ACTION_NONE;
        if(i < 4) {
            _voicesOut[i].connect(_voices[i].getOutput(), 0, _mixer1, i);
            _mixer1.gain(i, 1.0 / 6.0);
        } else {
            _voicesOut[i].connect(_voices[i].getOutput(), 0, _mixer2, i % 4);
            _mixer2.gain(i % 4, 1.0 / 6.0);
        }
    }
    _mixer1Out.connect(_mixer1, 0, _finalMixer, 0);
    _mixer2Out.connect(_mixer2, 0, _finalMixer, 1);
}

void SynthwavePoly::onEvent(Event ev)
{
    if(ev.type == Pulse || ev.action == ACTION_NONE) return;
    if(ev.type == NoteOn) {
        int index = findFreeIndex(ev.action);
        if(index == -1) return;
        _voices[index].onEvent(ev);
        _notes[index] = ev.action;
        _active_voices++;
    } else if(ev.type == NoteOff) {
        int index = voiceIndex(ev.action);
        if(index == -1) return;
        _voices[index].onEvent(ev);
        _notes[index] = -1;
        _active_voices--;
    }
}

const char *SynthwavePoly::getName() const
{
    return "SynthwavePoly";
}

const String SynthwavePoly::getActionName(int i) const
{
    return _voices[0].getActionName(i);
}

int SynthwavePoly::getSettingsCount() const
{
    return _voices[0].getSettingsCount();
}

const char *SynthwavePoly::getSettingName(int i) const
{
    return _voices[0].getSettingName(i);
}

void SynthwavePoly::configureSetting(int setting, int value)
{
    AudioNoInterrupts();
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        _voices[i].configureSetting(setting, value);
    }
    AudioInterrupts();
}

int SynthwavePoly::getSettingValue(int i) const
{
    return _voices[0].getSettingValue(i);
}

String SynthwavePoly::logSetting(int i)
{
    return _voices[0].logSetting(i);
}

void SynthwavePoly::update()
{
    AudioNoInterrupts();
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        _voices[i].update();
    }
    if(_active_voices >= 6) {
        for(int i = 0 ; i < 4 ; i++) {
            _mixer1.gain(i, 1.0 / _active_voices);
            _mixer2.gain(i, 1.0 / _active_voices);
        }
    }
    AudioInterrupts();
}

AudioStream &SynthwavePoly::getOutput()
{
    return _finalMixer;
}

int SynthwavePoly::voiceIndex(const int note) const
{
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        if(_notes[i] == note) return i;
    }
    return -1;
}

int SynthwavePoly::findFreeIndex(const int note) const
{
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        if(_notes[i] == -1) return i;
    }
    return -1;
}
