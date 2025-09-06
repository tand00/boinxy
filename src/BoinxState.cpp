#include <BoinxState.h>

#include <Screen.h>
#include <AppPage.h>

void BoinxState::execute(Event e) const 
{
    instruments[e.instrument]->onEvent(e);
}

bool BoinxState::has_changed(const BoinxState &other) const
{
    return (alter != other.alter) || (page_index != other.page_index);
}

AppPage *BoinxState::page()
{
    return pages[page_index];
}

void BoinxState::nextPage()
{
    page()->leave(this);
    screen->clearPageMessage();
    page_index = (page_index + 1) % N_PAGES;
    page()->enter(this);
}

void BoinxState::update()
{
    joystick->update();
    keyboard->update();
    page()->update(this);
    screen->update(this);
}
