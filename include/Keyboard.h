#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Button.h"

// Last two keys are octave up then down
#define KEYBOARD_SIZE 14

class Keyboard {

    public:

        Keyboard(uint8_t* pins, uint8_t c_pos = 1);
        ~Keyboard();

        void setup();
        void update();

        int8_t octave() const;
        void octave_up();
        void octave_down();
        void set_octave(int8_t o);

        int8_t note_number(int8_t button);

    private:

        int8_t _octave = 4;
        uint8_t _c_pos;
        Button* _buttons[KEYBOARD_SIZE];

};

#endif
