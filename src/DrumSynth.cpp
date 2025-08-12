#include <DrumSynth.h>

DrumSynth::DrumSynth()
{
    
}

void DrumSynth::onEvent(Event)
{
    
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
