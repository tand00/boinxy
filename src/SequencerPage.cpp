#include <SequencerPage.h>

#include <Screen.h>

SequencerPage::SequencerPage(SamplePlayer *player, SampleLibrary *samples)
    : _player(player)
    , _samples(samples)
{ }

const char *SequencerPage::name() const
{
    return "Sequencer";
}

void SequencerPage::enter(BoinxState *state)
{
    update_led = true;
}

void SequencerPage::leave(BoinxState *state)
{
    update_led = true;
}

void SequencerPage::update(BoinxState* state)
{
    update_led = false;
    if(state->keyboard->topKey(0) == JustPressed) {
        _samples->previousCategory();
        markForUpdate();
    }
    if(state->keyboard->topKey(1) == JustPressed) {
        _samples->nextCategory();
        markForUpdate();
    }
    if(state->keyboard->topKey(2) == JustPressed) {
        _samples->previousSample();
        markForUpdate();
    }
    if(state->keyboard->topKey(4) == JustPressed) {
        _samples->nextSample();
        markForUpdate();
    }
    if(state->keyboard->topKey(3) == JustPressed) {
        _player->playSample(_samples->getPath());
    }
    if(state->joystick->button.fallingEdge()) {
        if(channel == _player->channels()) {
            _player->registerSample(_samples->getPath());
        } else {
            _player->registerSampleAt(_samples->getPath(), channel);
        }
        state->screen->message(String("Registered channel " + channel));
        markForUpdate();
    }
    if(state->keyboard->up() == JustPressed) {
        if(state->alter) {
            state->sequencer->backward();
        } else {
            selection_len = min(selection_len + 1, MAX_SELECTION);
            if(selected + selection_len >= MAX_SELECTION) {
                selected = MAX_SELECTION - selection_len;
            }
        }
        update_led = true;
    }
    if(state->keyboard->down() == JustPressed) {
        if(state->alter) {
            state->sequencer->forward();
        } else if(selection_len > 1) {
            selection_len--;
        }
        update_led = true;
    }
    if(state->joystick->up() == JustPressed) {
        channel = min(min(channel + 1, _player->channels()), MAX_SAMPLES - 1);
        update_led = true;
        markForUpdate();
    }
    if(state->joystick->down() == JustPressed) {
        if(channel > 0) channel--;
        update_led = true;
        markForUpdate();
    }
    if(state->joystick->left() == JustPressed) {
        if(selected > 0) selected--;
        update_led = true;
    }
    if(state->joystick->right() == JustPressed) {
        selected = min(selected + 1, MAX_SELECTION - selection_len);
        update_led = true;
    }
    if(state->keyboard->bottomKey(0) == JustPressed) {
        Event e = generateEvent();
        for(int i = 0 ; i < 8 * selection_len ; i++) {
            state->sequencer->removeEvent(selected * 8 + i, e);
        }
        update_led = true;
    }
    for(int i = 0 ; i < 8 ; i++) {
        if(state->keyboard->bottomKey(i + 1) == JustPressed) {
            if(state->alter) {
                if(i < 4) { // Quantization
                    state->sequencer->setStepsPerPulse(i + 1);
                    state->screen->message(String("Steps/p : ") + (i + 1));
                } else { // 
                    
                }
                continue;
            }
            Event e = generateEvent();
            for(int bar = 0 ; bar < selection_len ; bar++) {
                int step = (selected * 8) + (bar * 8) + i;
                state->sequencer->toggleEvent(step, e);
            }
            update_led = true;
        }
    }
}

void SequencerPage::display(BoinxState *state)
{
    state->screen->pageMessage(
        String(_samples->getCategory()->name()) + "\n" 
        + _samples->getSample()->name() + "\n" 
        + ((_player->channels() > channel) ? (_player->getActionName(channel)) + 9 : "")
    );
}

Event SequencerPage::generateEvent()
{
    return Event { Pulse, channel, SAMPLE_PLAYER_I };
}
