#include <FMSynth.h>

#include <Solfagus.h>

FMSynth::FMSynth()
{
    _modulatorOut.connect(_modulator, _modulationEnvelope);
    _modulationEnvelopeOut.connect(_modulationEnvelope, 0, _carrier, 0);
    _carrierOut.connect(_carrier, _envelope);
    _envelopeOut.connect(_envelope, _amp);
}

void FMSynth::onEvent(Event ev)
{
    if(ev.type == Pulse) return;
    if(ev.type == NoteOff && ev.action == _note) {
        AudioNoInterrupts();
        _envelope.noteOff();
        _modulationEnvelope.noteOff();
        AudioInterrupts();
        return;
    }
    if(ev.type != NoteOn) return;
    AudioNoInterrupts();
    setNote(ev.action);
    _envelope.noteOn();
    _modulationEnvelope.noteOn();
    AudioInterrupts();
}

const char *FMSynth::getName() const
{
    return "FMSynth";
}

const String FMSynth::getActionName(int16_t i) const
{
    return Solfagus::noteName(i);
}

uint8_t FMSynth::getSettingsCount() const
{
    return 0;
}

const char *FMSynth::getSettingName(uint8_t i) const
{
    return "unkown";
}

void FMSynth::configureSetting(uint8_t setting, int value)
{
}

int FMSynth::getSettingValue(uint8_t i) const
{
    return 0;
}

String FMSynth::logSetting(uint8_t i)
{
    return String();
}

void FMSynth::update()
{
}

AudioStream &FMSynth::getOutput()
{
    return _amp;
}

void FMSynth::setNote(int8_t note)
{
}
