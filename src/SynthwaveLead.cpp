#include <SynthwaveLead.h>
#include <Solfagus.h>

SynthwaveLead::SynthwaveLead()
{
    _osc1Out.connect(_osc1, 0, _mixer, 0);
    _osc2Out.connect(_osc2, 0, _mixer, 1);
    _osc3Out.connect(_osc3, 0, _mixer, 2);
    _mixerOut.connect(_mixer, 0, _envelope, 0);
    _envelopeOut.connect(_envelope, 0, _filter, 0);
    _filterOut.connect(_filter, 0, _amp, 0);
    
    _amp.gain(_volume / 100.0);
    _filter.resonance(0.707);
    _filter.frequency(_low_pass * 25.0);
    _envelope.sustain(_sustain / 100.0);
    _osc1.begin(0.25, 440.0, WAVEFORM_SAWTOOTH);
    _osc2.begin(0.25, 440.0, WAVEFORM_SAWTOOTH);
    _osc3.begin(0.25, 440.0, WAVEFORM_SAWTOOTH);
    setNote(12 * 4 + NOTE_A);
}

void SynthwaveLead::onEvent(Event ev)
{
    if(ev.type == Pulse) return;
    if(ev.type == NoteOff && ev.action == _note) {
        _envelope.noteOff();
        return;
    }
    if(ev.type != NoteOn) return;
    setNote(ev.action);
    _envelope.noteOn();
}

const char *SynthwaveLead::getName() const
{
    return "SynthwaveLead";
}

const String SynthwaveLead::getActionName(int i) const
{
    return Solfagus::noteName(i);
}

String SynthwaveLead::logSetting(int i)
{
    switch(i) {
    case 1:
        return String("Detune : ") + (_detune / 20.0);
    case 2:
        return String("Filter : ") + (_low_pass * 25.0) + "Hz";
    default:
        return Instrument::logSetting(i);
    }    
}

void SynthwaveLead::update()
{
}

AudioStream &SynthwaveLead::getOutput()
{
    return _amp;
}

void SynthwaveLead::setNote(int8_t note)
{
    float freq = Solfagus::noteFrequency(note);
    _note = note;
    float det = _detune / 2000.0;
    AudioNoInterrupts();
    _osc1.frequency(freq);
    _osc2.frequency(freq * (1 + det));
    _osc3.frequency(freq * (1 - det));
    AudioInterrupts();
}

int SynthwaveLead::getSettingsCount() const
{
    return 5;
}

const char *SynthwaveLead::getSettingName(int i) const
{
    switch(i) {
    case 0:
        return "volume";
    case 1:
        return "detune";
    case 2:
        return "filter";
    case 3:
        return "sustain";
    case 4:
        return "n osc";
    }
    return "unknown";
}

void SynthwaveLead::configureSetting(int setting, int value)
{
    if(setting == 0) {
        _volume = min(max(0, value), 200);
        _amp.gain(_volume / 100.0);
    } else if(setting == 1) {
        _detune = min(max(0, value), 100);
        setNote(_note);
    } else if(setting == 2) {
        _low_pass = min(max(0, value), 200);
        _filter.frequency(_low_pass * 25.0);
    } else if(setting == 3) {
        _sustain = min(max(0, value), 100);
        _envelope.sustain(_sustain / 100.0);
    } else if(setting == 4) {
        _n_osc = min(max(1, value), 3);
        AudioNoInterrupts();
        for(int i = 1 ; i < 3 ; i++) {
            if(i < _n_osc) _mixer.gain(i, 1.0);
            else _mixer.gain(i, 0.0);
        }
        _osc1.amplitude(1.0 / _n_osc);
        _osc2.amplitude(1.0 / _n_osc);
        _osc3.amplitude(1.0 / _n_osc);
        AudioInterrupts();
    } 
}

int SynthwaveLead::getSettingValue(int i) const
{
    switch(i) {
    case 0:
        return _volume;
    case 1:
        return _detune;
    case 2:
        return _low_pass;
    case 3:
        return _sustain;
    case 4:
        return _n_osc;
    default:
        return 0;
    }
}
