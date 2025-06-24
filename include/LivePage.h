#ifndef LIVE_PAGE_H
#define LIVE_PAGE_H

#include "AppPage.h"

class LivePage : public AppPage {

    using AppPage::AppPage;

    public:

        void update() override;

        void toggleRecord();

    private:

        uint8_t _instrument = 0;
        bool _record = false;
        
};

#endif
