#include "NaiveSynth.h"

NaiveSynth::NaiveSynth()
{
    
}

void NaiveSynth::onEvent(Event ev)
{

}

const char* NaiveSynth::getName() const
{
    return "NaiveSynth";
}

const char* NaiveSynth::getActionName(int i) const
{
    return nullptr;
}

AudioStream& NaiveSynth::getOutput()
{
    return _amp;
}
