#ifndef SEQUENCER_PAGE_H
#define SEQUENCER_PAGE_H

#include <AppPage.h>

class SequencerPage : public AppPage {

    using AppPage::AppPage;

    public:

        void update() override;

    private:

        Event _event = { Pulse, 0, 0 };

};

#endif