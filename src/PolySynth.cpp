#include <PolySynth.h>

template class PolySynth<SynthwaveLead>;
template class PolySynth<FMSynth>;

template<class T>
PolySynth<T>::PolySynth(String name)
    : _name(name)
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

template<class T>
void PolySynth<T>::onEvent(Event ev)
{
    if(ev.type == Pulse || ev.isNone()) return;
    if(ev.type == NoteOn) {
        if(voiceIndex(ev.action) >= 0) return;
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

template<class T>
const char *PolySynth<T>::getName() const
{
    return _name.c_str();
}

template<class T>
const String PolySynth<T>::getActionName(int16_t i) const
{
    return _voices[0].getActionName(i);
}

template<class T>
uint8_t PolySynth<T>::getSettingsCount() const
{
    return _voices[0].getSettingsCount();
}

template<class T>
const char *PolySynth<T>::getSettingName(uint8_t i) const
{
    return _voices[0].getSettingName(i);
}

template<class T>
void PolySynth<T>::configureSetting(uint8_t setting, int value)
{
    AudioNoInterrupts();
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        _voices[i].configureSetting(setting, value);
    }
    AudioInterrupts();
}

template<class T>
int PolySynth<T>::getSettingValue(uint8_t i) const
{
    return _voices[0].getSettingValue(i);
}

template<class T>
String PolySynth<T>::logSetting(uint8_t i)
{
    return _voices[0].logSetting(i);
}

template<class T>
void PolySynth<T>::update()
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

template<class T>
AudioStream &PolySynth<T>::getOutput()
{
    return _finalMixer;
}

template<class T>
int PolySynth<T>::voiceIndex(const int note) const
{
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        if(_notes[i] == note) return i;
    }
    return -1;
}

template<class T>
int PolySynth<T>::findFreeIndex(const int note) const
{
    for(int i = 0 ; i < N_SYNTH_VOICES ; i++) {
        if(_notes[i] == -1) return i;
    }
    return -1;
}
