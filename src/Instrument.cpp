#include <Instrument.h>

uint8_t Instrument::getSettingsCount() const
{
    return 0;
}

void Instrument::incrSetting(uint8_t i)
{
    this->configureSetting(i, this->getSettingValue(i) + 1);
}

void Instrument::decrSetting(uint8_t i)
{
    this->configureSetting(i, this->getSettingValue(i) - 1);
}

String Instrument::logSetting(uint8_t i)
{
    return String(getSettingName(i)) + ":" + getSettingValue(i);
}
