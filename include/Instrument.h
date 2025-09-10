#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <Event.h>
#include <Audio.h>

class Instrument {

    public:

        virtual void onEvent(Event) = 0;
        virtual const char* getName() const = 0;
        virtual const String getActionName(int i) const = 0;

        virtual int getSettingsCount() const;
        virtual const char* getSettingName(int i) const { return "unknown"; }
        virtual void configureSetting(int setting, int value) {}
        virtual int getSettingValue(int i) const { return 0; }

        void incrSetting(int i);
        void decrSetting(int i);

        virtual String logSetting(int i);

        virtual void update() {}

        virtual AudioStream& getOutput() = 0;

};

#endif
