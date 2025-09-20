#ifndef SEQUENCER_PAGE_H
#define SEQUENCER_PAGE_H

#include <AppPage.h>
#include <Event.h>
#include <SamplePlayer.h>
#include <SampleLibrary.h>

#define MAX_SELECTION 4
#define TOTAL_SEQUENCER_RANGE 16

class SequencerPage : public AppPage {

    public:

        SequencerPage(SamplePlayer* player, SampleLibrary* samples);

        const char* name() const override;

        void enter(BoinxState* state) override;
        void leave(BoinxState* state) override;

        void update(BoinxState* state) override;

        void display(BoinxState* state) override;

        Event generateEvent();

        uint8_t selected = 0;
        uint8_t selection_len = 1;
        uint8_t channel = 0;
        bool update_led = false;

    private:

        void incrSelectionLen();
        void decrSelectionLen();
        void incrSelection();
        void decrSelection();

        bool _global_mode = false;

        SamplePlayer* _player;
        SampleLibrary* _samples;
        Event _event = { Pulse, 0, 0 };

};

#endif