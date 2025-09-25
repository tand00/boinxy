#include <SynthwaveLead.h>
#include <Solfagus.h>

SynthwaveLead::SynthwaveLead()
{
    _osc1Out.connect(_osc1, 0, _mixer, 0);
    _osc2Out.connect(_osc2, 0, _mixer, 1);
    _osc3Out.connect(_osc3, 0, _mixer, 2);
    _mixerOut.connect(_mixer, 0, _envelope, 0);
    _envelopeOut.connect(_envelope, 0, _filter, 0);
    _filterOut.connect(_filter, 0, _crusher, 0);
    _crusherOut.connect(_crusher, 0, _amp, 0);
    
    _amp.gain(_volume / 20.0);
    _filter.resonance(0.707);
    _filter.frequency(_low_pass * 25.0);
    _crusher.bits(_crusher_bits);
    _crusher.sampleRate(_crusher_freq * 441);
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

const String SynthwaveLead::getActionName(int16_t i) const
{
    return Solfagus::noteName(i);
}

String SynthwaveLead::logSetting(uint8_t i)
{
    String str = String(getSettingName(i)) + ":";
    switch(i) {
    case 0:
        return str + (_volume * 5);
    case 1:
        return str + (_detune / 20.0);
    case 2:
        return str + (_low_pass * 25);
    case 6:
        return str + (_crusher_freq * 441);
    default:
        return str + getSettingValue(i);
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

uint8_t SynthwaveLead::getSettingsCount() const
{
    return 7;
}

const char *SynthwaveLead::getSettingName(uint8_t i) const
{
    switch(i) {
    case 0:
        return "Vol";
    case 1:
        return "Det";
    case 2:
        return "LoP";
    case 3:
        return "Sus";
    case 4:
        return "nOs";
    case 5:
        return "crB";
    case 6:
        return "crF";
    }
    return "unknown";
}

void SynthwaveLead::configureSetting(uint8_t setting, int value)
{
    if(setting == 0) {
        _volume = min(max(0, value), 40);
        _amp.gain(_volume / 20.0);
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
    } else if(setting == 5) {
        _crusher_bits = min(max(1, value), 16);
        _crusher.bits(_crusher_bits);
    } else if(setting == 6) {
        _crusher_freq = min(max(1, value), 100);
        _crusher.sampleRate(_crusher_freq * 441);
    } 
}

int SynthwaveLead::getSettingValue(uint8_t i) const
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
    case 5:
        return _crusher_bits;
    case 6:
        return _crusher_freq;
    default:
        return 0;
    }
}
