#include <HarmonicaPage.h>

#include <Screen.h>

const char *HarmonicaPage::name() const
{
    return "Harmonica";
}

void HarmonicaPage::update(BoinxState *state)
{
    for(int i = 0 ; i < 9 ; i++) {
        int8_t notes[4] = { 0 };
        int n = 3;
        int8_t at = i == 0 ? 7 : (i - 1);
        int8_t octave = i == 0 ? (_octave - 1) : _octave;
        if(state->joystick->isReleased()) {
            if(state->keyboard->bottomKey(i) == JustPressed && !state->alter) {
                state->solfagus->chordAt(at, notes, octave, n);
                chordOn(state, notes, n);
            }
            if(state->keyboard->bottomKey(i) == JustReleased && !state->alter) {
                state->solfagus->chordAt(at, notes, octave, n);
                chordOff(state, notes, n);
            }
        } else {
            
        }
    }
}

void HarmonicaPage::display(BoinxState *state)
{
    String key = state->solfagus->getKey().toString();
    state->screen->pageMessage(String("Key : ") + key + "\n" + _currentChord);

}

void HarmonicaPage::chordOn(BoinxState* state, int8_t chord[], int8_t n)
{
    for(int i = 0 ; i < n ; i++) {
        Event e { NoteOn, chord[i], _instrument };
        state->execute(e);
        state->sequencer->feed(e);
    }
}

void HarmonicaPage::chordOff(BoinxState* state, int8_t chord[], int8_t n)
{
    for(int i = 0 ; i < n ; i++) {
        Event e { NoteOff, chord[i], _instrument };
        state->execute(e);
        state->sequencer->feed(e);
    }
}
