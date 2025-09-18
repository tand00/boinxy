#include <BoinxState.h>

#include <Screen.h>
#include <AppPage.h>

void BoinxState::execute(Event e) const
{
    if(e.instrument >= N_INSTRUMENTS || e.action == ACTION_NONE) return;
    instruments[e.instrument]->onEvent(e);
}

bool BoinxState::has_changed(const BoinxState &other) const
{
    return (alter != other.alter) || 
        (page_index != other.page_index);
}

AppPage *BoinxState::page()
{
    return pages[page_index];
}

void BoinxState::nextPage()
{
    page()->leave(this);
    screen->clearPageMessage();

    panel->encoder1.write(0);
    panel->encoder2.write(0);
    panel->encoder3.write(0);

    page_index = (page_index + 1) % N_PAGES;
    page()->enter(this);
    page()->markForUpdate();
}

void BoinxState::setup()
{
    joystick->setup();
    keyboard->setup();
    screen->setup(*this);
}

void BoinxState::update()
{
    joystick->update();
    keyboard->update();
    panel->update();
    page()->update(this);
    page()->checkDisplayUpdate(this);
    screen->update(this);

    for(int i = 0 ; i < N_INSTRUMENTS ; i++) {
        instruments[i]->update();
    }

    if(sequencer->step_flag) {
        Event* events = sequencer->getEvents();
        Event* previous = sequencer->getPreviousEvents();
        for(int i = 0 ; i < MAX_EVENTS_PER_STEP ; i++) {
            if(events[i].type == Pulse || events[i].type == NoteOn) {
                execute(events[i]);
            }
            if(previous[i].type == NoteOff) {
                execute(previous[i]);
            }
        }
    }
}

void FrontPanel::update()
{
    button2.update();
    button3.update();
    encoder1Btn.update();
    encoder2Btn.update();
    encoder3Btn.update();
}
