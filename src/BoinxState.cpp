#include <BoinxState.h>

#include <Screen.h>
#include <AppPage.h>

void BoinxState::execute(Event e)
{
    if(e.instrument >= N_INSTRUMENTS || e.isNone()) return;
    if(!updateActiveEvents(e)) return;
    instruments[e.instrument]->onEvent(e);
}

void BoinxState::flush()
{
    for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
        Event& e = active_events[i];
        if(e.isNone()) continue;
        Event off = e.off();
        e.nonify();
        instruments[off.instrument]->onEvent(off);
    }
}

void BoinxState::flushInstrument(int instru)
{
    Serial.println(String("Flushing instrument : ") + instru);
    for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
        Event& e = active_events[i];
        if(e.isNone() || e.instrument != instru) continue;
        Event off = e.off();
        e.nonify();
        instruments[off.instrument]->onEvent(off);
    }
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

bool BoinxState::updateActiveEvents(Event e)
{
    if(e.type == NoteOn) {
        for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
            if(active_events[i].isNone()) {
                active_events[i] = e;
                return true;
            }
        }
        Serial.println("! Reached maximum number of ON events !");
        return false;
    } else if(e.type == NoteOff) {
        for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
            if(e.isSameAction(active_events[i])) {
                active_events[i].nonify();
            }
        }
        return true;
    }
    return true;
}

void FrontPanel::update()
{
    button2.update();
    button3.update();
    encoder1Btn.update();
    encoder2Btn.update();
    encoder3Btn.update();
}
