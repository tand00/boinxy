#include <NaiveSynth.h>
#include <Solfagus.h>

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

const String NaiveSynth::getActionName(int i) const
{
    return Solfagus::noteName(i);
}

AudioStream& NaiveSynth::getOutput()
{
    return _amp;
}
