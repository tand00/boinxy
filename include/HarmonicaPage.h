#ifndef HARMONICA_H
#define HARMONICA_H

#include <AppPage.h>

class HarmonicaPage : public AppPage {

    public:

        const char* name() const override;

        void update(BoinxState* state) override;

        void display(BoinxState* state) override;

        void chordOn(BoinxState* state, int8_t chord[], int8_t n);
        void chordOff(BoinxState* state, int8_t chord[], int8_t n);
    
    private:

        String _currentChord;
        int8_t _octave = 4;
        int8_t _instrument = 0;

};

#endif