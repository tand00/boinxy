#include <NaiveSynth.h>
#include <Solfagus.h>

NaiveSynth::NaiveSynth()
{
    for(int i = 0 ; i < N_VOICES ; i++) {
        _waves[i].begin(1.0, 440.0, mappedShape());
        _voices[i] = -1;
        _connections[i].connect(_waves[i], _envelopes[i]);
        if(i < 4) {
            _connections[N_VOICES + i].connect(_envelopes[i], 0, _mixer1, i);
        } else {
            _connections[N_VOICES + i].connect(_envelopes[i], 0, _mixer2, i % 4);
        }
        
    }
    _mixer1Out.connect(_mixer1, 0, _finalMixer, 0);
    _mixer2Out.connect(_mixer2, 0, _finalMixer, 1);
    _finalMixerOut.connect(_finalMixer, 0, _amp, 0);
    _ampOut.connect(_amp, 0, _filter, 0);
    _amp.gain(_volume / 100.0);
    _filter.frequency(_low_pass * 25.0);
    _filter.resonance(0.707);
}

void NaiveSynth::onEvent(Event ev)
{
    if(ev.type == Pulse || ev.action == ACTION_NONE) return;
    if(ev.type == NoteOn) {
        float freq = Solfagus::noteFrequency(ev.action);
        int index = findFreeIndex(ev.action);
        if(index == -1) return;
        _voices[index] = ev.action;
        AudioNoInterrupts();
        _waves[index].frequency(freq);
        _envelopes[index].noteOn();
        AudioInterrupts();
    } else if(ev.type == NoteOff) {
        int index = voiceIndex(ev.action);
        if(index == -1) return;
        _voices[index] = -1;    
        _envelopes[index].noteOff();
    }
}

const char* NaiveSynth::getName() const
{
    return "NaiveSynth";
}

const String NaiveSynth::getActionName(int i) const
{
    return Solfagus::noteName(i);
}

AudioStream& NaiveSynth::getOutput()
{
    return _filter;
}

int NaiveSynth::getSettingsCount() const
{
    return 4;
}

const char *NaiveSynth::getSettingName(int i) const
{
    switch(i) {
    case 0:
        return "shape";
    case 1:
        return "volume";
    case 2:
        return "filter";
    default:
        return "unknown";
    }
}

void NaiveSynth::configureSetting(int setting, int value)
{
    if(setting == 0) {
        _shape = min(max(0, value), 3);
        AudioNoInterrupts();
        for(int i = 0 ; i < N_VOICES ; i++) {
            _waves[i].begin(mappedShape());
        }
        AudioInterrupts();
    } else if(setting == 1) {
        _volume = min(max(0, value), 200);
        _amp.gain(_volume / 100.0);
    } else if(setting == 2) {
        _low_pass = min(max(0, value), 200);
        _filter.frequency(_low_pass * 25.0);
    }
}

int NaiveSynth::getSettingValue(int i) const
{
    switch(i){
    case 0:
        return _shape;
    case 1:
        return _volume;
    case 2:
        return _low_pass;
    default:
        return 0;
    }
}

void NaiveSynth::update()
{
    int count = 0;
    for(int i = 0 ; i < N_VOICES ; i++) {
        if(_envelopes[i].isActive()) count++;
    }
    if(count != _active_voices) {
        _active_voices = count;
        AudioNoInterrupts();
        for(int i = 0 ; i < 4 ; i++) {
            _mixer1.gain(i, 
                (_active_voices == 0) ? 1.0 : (1.0 / (float) _active_voices)
            );
        }
        AudioInterrupts();
    }
}

String NaiveSynth::logSetting(int i)
{
    String str;
    switch(i) {
    case 0:
        str = "Shape : ";
        switch(_shape) {
        case 0:
            str += "sin";
            break;
        case 1:
            str += "saw";
            break;
        case 2:
            str += "sq";
            break;
        case 3:
            str += "tri";
            break;
        }
        return str;
    case 2:
        return String("Filter : ") + (_low_pass * 25.0) + "Hz";
    default:
        return Instrument::logSetting(i);
    }
}

int NaiveSynth::voiceIndex(const int note) const
{
    for(int i = 0 ; i < N_VOICES ; i++) {
        if(_voices[i] == note) {
            return i;
        }
    }
    return -1;
}

int NaiveSynth::findFreeIndex(const int note) const
{
    for(int i = 0 ; i < N_VOICES ; i++) {
        if(_voices[i] == -1) {
            return i;
        }
    }
    return -1;
}

short NaiveSynth::mappedShape() const
{
    return _shape;
}
