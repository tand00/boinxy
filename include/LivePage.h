#ifndef LIVE_PAGE_H
#define LIVE_PAGE_H

#include <AppPage.h>

#define DEFAULT_LIVE_PAGE_OCTAVE 4

class LivePage : public AppPage {

    public:

        const char* name() const override;

        void update(BoinxState* state) override;

        void display(BoinxState* state) override;

        int16_t noteIndex(const int16_t i) const;

        void noteOn(const int16_t i, BoinxState* state) const;
        void noteOff(const int16_t i, BoinxState* state) const;

    private:

        uint8_t _instrument = 0;
        int8_t _octave = DEFAULT_LIVE_PAGE_OCTAVE;
        uint8_t _settings_offset = 0;
        
};

#endif
