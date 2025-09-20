#include <LivePage.h>
#include <Screen.h>

const char *LivePage::name() const
{
    return "Live";
}

void LivePage::update(BoinxState *state)
{
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
        markForUpdate();
    }
    for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
        if(state->keyboard->pianoKey(i) == JustPressed && !state->alter) {
            noteOn(noteIndex(i), state);
        }
        if(state->keyboard->pianoKey(i) == JustReleased && !state->alter) {
            noteOff(noteIndex(i), state);
        }
    }
    for(int i = 1 ; i < 5 ; i ++) {
        if(state->keyboard->bottomKey(i) == JustPressed && state->alter) {
            _settings_offset = i - 1;
            state->screen->message(String("Settings page ") + i);
        }
    } 
    Encoder* encoders[3] = { 
        &state->panel->encoder1,
        &state->panel->encoder2,
        &state->panel->encoder3
    };
    Instrument* instru = state->instruments[_instrument];
    int offset = _settings_offset * 6;
    for(int i = 0 ; i < min(instru->getSettingsCount() - offset, 6) ; i++) {
        if(i < 3 && state->alter) continue;
        if(i >= 3 && !state->alter) continue;
        Encoder* encoder = encoders[i % 3];
        int e_value = encoder->read() / 4;
        if(e_value > 0) {
            encoder->write(0);
            instru->incrSetting(offset + i);
            state->screen->message(instru->logSetting(offset + i));
        } else if(e_value < 0) {
            encoder->write(0);
            instru->decrSetting(offset + i);
            state->screen->message(instru->logSetting(offset + i));
        }
    }
    if(state->panel->button2.fallingEdge()) {
        state->sequencer->toggleRecord();
    }
    if(state->alter && state->keyboard->bottomKey(0) == JustPressed) {
        state->sequencer->purgeInstrument(_instrument);
        state->flushInstrument(_instrument);
    }
}

void LivePage::display(BoinxState *state)
{
    state->screen->pageMessage(
        // String("Instrument :\n") + 
        state->instruments[_instrument]->getName()
    );
}

int LivePage::noteIndex(const int i) const
{
    return _octave * 12 + FIRST_KEYBOARD_NOTE + i;
}

void LivePage::noteOn(const int i, BoinxState* state) const
{
    Event e { NoteOn, i, _instrument };
    state->execute(e);
    state->sequencer->feed(e);
}

void LivePage::noteOff(const int i, BoinxState* state) const
{
    Event e { NoteOff, i, _instrument };
    state->execute(e);
    state->sequencer->feed(e);
}
