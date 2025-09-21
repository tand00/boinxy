#include <AppPage.h>

bool AppPage::needsScreenUpdate() const
{
    return _updateDisplay;
}

void AppPage::markForUpdate()
{
    _updateDisplay = true;
}

 void AppPage::markUpdated()
{
    _updateDisplay = false;
}
