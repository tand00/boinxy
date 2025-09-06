#ifndef SEQUENCER_PAGE_H
#define SEQUENCER_PAGE_H

#include <AppPage.h>
#include <Event.h>
#include <SamplePlayer.h>
#include <SampleLibrary.h>

class SequencerPage : public AppPage {

    public:

        SequencerPage(SamplePlayer* player, SampleLibrary* samples);

        const char* name() const override;

        void update(BoinxState* state) override;

    private:

        SamplePlayer* _player;
        SampleLibrary* _samples;
        Event _event = { Pulse, 0, 0 };

};

#endif