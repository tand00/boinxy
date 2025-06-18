#include <Keyboard.h>

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

void Keyboard::reset() {
    for(int i = 0 ; i < N_NOTES ; i++) {
        _notes_status[i] = false;
    }
}

int8_t Keyboard::octave() const {
    return _octave;
}

void Keyboard::octaveUp() {
    setOctave(min(_octave + 1, 8));
}

void Keyboard::octaveDown() {
    setOctave(max(_octave - 1, -2));
}

void Keyboard::setOctave(int8_t o) {
    _octave = min(max(o, (int8_t) -2), (int8_t) 8);
    reset();
}

void Keyboard::update() {
    for(int i = 0 ; i < KEYBOARD_SIZE - 2 ; i++) {
        ButtonState state = _buttons[i]->update();
        int8_t note = noteNumber(i);
    }
    if(_buttons[KEYBOARD_SIZE - 2]->update() == JustPressed) {
        octaveDown();
    }
    if(_buttons[KEYBOARD_SIZE - 1]->update() == JustPressed) {
        octaveUp();
    }
}

int8_t Keyboard::noteNumber(int8_t button) {
    int8_t note = 24 + (_octave * 12) + (button - _c_pos);
    return min(max(note, (int8_t) 0), (int8_t) 127);
}

