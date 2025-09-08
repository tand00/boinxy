#include <LivePage.h>
#include <Screen.h>

const char *LivePage::name() const
{
    return "Live";
}

void LivePage::enter(BoinxState *state)
{
    displayPage(state);
}

void LivePage::update(BoinxState *state)
{
    bool update = false;
    if(state->keyboard->up() == JustPressed) {
        _octave = min(_octave + 1, 8);
        state->screen->message(String("Octave : ") + _octave);
    }
    if(state->keyboard->down() == JustPressed) {
        _octave = max(_octave - 1, 0);
        state->screen->message(String("Octave : ") + _octave);
    }
    if(state->change_signal) {
        _instrument = (_instrument + 1) % N_INSTRUMENTS;
        update = true;
    }
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        if(state->keyboard->pianoKey(i) == JustPressed && !state->alter) {
            Event e { NoteOn, noteIndex(i), _instrument };
            state->execute(e);
        }
        if(state->keyboard->pianoKey(i) == JustReleased && !state->alter) {
            Event e { NoteOff, noteIndex(i), _instrument };
            state->execute(e);
        }
    }
    if(update) {
        displayPage(state);
    }
}

void LivePage::leave(BoinxState *state)
{
    displayPage(state);
}

void LivePage::toggleRecord() 
{
    _record = !_record;
}

void LivePage::displayPage(BoinxState *state)
{
    state->screen->pageMessage(
        String("Instrument :\n") + state->instruments[_instrument]->getName()
    );
}

int LivePage::noteIndex(const int i) const
{
    return _octave * 12 + FIRST_KEYBOARD_NOTE + i;
}
