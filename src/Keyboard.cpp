#include "Keyboard.h"

Keyboard::Keyboard(uint8_t* pins, uint8_t c_pos) 
    : _c_pos(c_pos)
{
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        _buttons[i] = new Button(pins[i]);
    }
}

Keyboard::~Keyboard() {
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        delete _buttons[i];
    }
}

void Keyboard::setup() {
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        _buttons[i]->setup();
    }
}

int8_t Keyboard::octave() const {
    return _octave;
}

void Keyboard::octave_up() {
    _octave = min(_octave + 1, 8);
}

void Keyboard::octave_down() {
    _octave = max(_octave - 1, -2);
}

void Keyboard::set_octave(int8_t o) {
    _octave = min(max(o, (int8_t) -2), (int8_t) 8);
}

void Keyboard::update() {
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        ButtonState state = _buttons[i]->update();
        int8_t note = note_number(i);
    }
}

int8_t Keyboard::note_number(int8_t button) {
    int8_t note = 24 + (_octave * 12) + (button - _c_pos);
    return min(max(note, (int8_t) 0), (int8_t) 127);
}

