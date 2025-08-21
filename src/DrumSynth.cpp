#include <DrumSynth.h>

#include <Solfagus.h>

DrumSynth::DrumSynth()
{
    
}

void DrumSynth::onEvent(Event e)
{
    double freq = Solfagus::noteFrequency(e.action);
    _drumSynth.frequency(freq);
    _drumSynth.noteOn();
}

const char* DrumSynth::getName() const
{
    return "DrumSynth";
}

const char* DrumSynth::getActionName(int i) const
{
    return nullptr;
}

AudioStream& DrumSynth::getOutput()
{
    return _drumSynth;
}
