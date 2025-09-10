#include <BoinxState.h>

#include <Screen.h>
#include <AppPage.h>

void BoinxState::execute(Event e) const
{
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
    page()->update(this);
    page()->checkDisplayUpdate(this);
    screen->update(this);

    for(int i = 0 ; i < N_INSTRUMENTS ; i++) {
        instruments[i]->update();
    }

    if(sequencer->step_flag) {
        uint8_t n_events = sequencer->getEventsCount();
        Event* events = sequencer->getEvents();
        for(int i = 0 ; i < n_events ; i++) {
            execute(events[i]);
        }
    }
}
