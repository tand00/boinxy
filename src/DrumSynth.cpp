#include <DrumSynth.h>

#include <Solfagus.h>

DrumSynth::DrumSynth()
{
    
}

void DrumSynth::onEvent(Event e)
{
    if(e.type == NoteOff) return;
    double freq = Solfagus::noteFrequency(e.action);
    _drumSynth.frequency(freq);
    _drumSynth.noteOn();
}

const char* DrumSynth::getName() const
{
    return "DrumSynth";
}

const String DrumSynth::getActionName(int i) const
{
    return Solfagus::noteName(i);
}

int DrumSynth::getSettingsCount() const
{
    return 3;
}

const char *DrumSynth::getSettingName(int i) const
{
    switch(i) {
        case 0:
            return "Len";
        case 1:
            return "Scd";
        case 2:
            return "PtM";
        default:
            return "unknown";
    }
}

void DrumSynth::configureSetting(int setting, int value)
{
    switch(setting) {
        case 0:
            _drumSynth.length(100 * value);
            break;
        case 1:
            _drumSynth.secondMix(0.1 * value);
            break;
        case 2:
            _drumSynth.pitchMod(0.1 * value);
            break;
    }
}

int DrumSynth::getSettingValue(int i) const
{
    return 0;
}

AudioStream& DrumSynth::getOutput()
{
    return _drumSynth;
}
