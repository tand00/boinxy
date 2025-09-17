#ifndef LIVE_PAGE_H
#define LIVE_PAGE_H

#include <AppPage.h>

#define DEFAULT_LIVE_PAGE_OCTAVE 4

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
        int _octave = DEFAULT_LIVE_PAGE_OCTAVE;
        bool _record = false;
        uint8_t _settings_offset = 0;
        
};

#endif
