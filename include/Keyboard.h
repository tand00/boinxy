#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Adafruit_MCP23X17.h>

#define N_NOTES 127 // MIDI note encoding

#include "Button.h"

// Last two keys are octave down then up
#define KEYBOARD_SIZE 14

class Keyboard {

    public:

        Keyboard();
        ~Keyboard();

        void setup();
        void update();
        void reset();

        int8_t octave() const;
        void octaveUp();
        void octaveDown();
        void setOctave(int8_t o);

        int8_t noteNumber(int8_t button);

    private:

        Adafruit_MCP23X17 _mcp;

        int8_t _octave = 4;
        uint8_t _c_pos;
        Button* _buttons[KEYBOARD_SIZE];

        bool _notes_status[N_NOTES] = { false };

};

#endif
