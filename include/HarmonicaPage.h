#ifndef HARMONICA_H
#define HARMONICA_H

#include <AppPage.h>

class HarmonicaPage : public AppPage {

    public:

        const char* name() const override;

        void update(BoinxState* state) override;

        void display(BoinxState* state) override;
    
    private:

        int _octave = 4;

};

#endif