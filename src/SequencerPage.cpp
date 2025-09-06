#include <SequencerPage.h>

SequencerPage::SequencerPage(SamplePlayer *player, SampleLibrary *samples)
    : _player(player)
    , _samples(samples)
{ }

const char *SequencerPage::name() const
{
    return "Sequencer";
}

void SequencerPage::update(BoinxState* state)
{
    
}
