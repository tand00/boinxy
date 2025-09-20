#include <HarmonicaPage.h>

#include <Screen.h>

const char *HarmonicaPage::name() const
{
    return "Harmonica";
}

void HarmonicaPage::update(BoinxState *state)
{
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        if(state->keyboard->pianoKey(i) == JustPressed && !state->alter) {
            // Event e { NoteOn, noteIndex(i), _instrument };
            // state->execute(e);
        }
        if(state->keyboard->pianoKey(i) == JustReleased && !state->alter) {
            // Event e { NoteOff, noteIndex(i), _instrument };
            // state->execute(e);
        }
    }
}

void HarmonicaPage::display(BoinxState *state)
{
    String key = state->solfagus->getKey().toString();
    state->screen->pageMessage(String("Key : ") + key);
}
