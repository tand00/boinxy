#ifndef LIVE_PAGE_H
#define LIVE_PAGE_H

#include <AppPage.h>

class LivePage : public AppPage {

    public:

        const char* name() const override;

        void update(BoinxState* state) override;
        
        void toggleRecord();

        void display(BoinxState* state) override;

        int noteIndex(const int i) const;

        void noteOn(const int i, BoinxState* state) const;
        void noteOff(const int i, BoinxState* state) const;

    private:

        uint8_t _instrument = 0;
        int _octave = 4;
        bool _record = false;
        
};

#endif
