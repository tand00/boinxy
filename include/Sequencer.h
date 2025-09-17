#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>
#include <Event.h>

#define MAX_SEQUENCER_STEPS 128
#define MAX_EVENTS_PER_STEP 32

#define DEFAULT_TEMPO 110
#define DEFAULT_TRACK_LEN 32
#define DEFAULT_STEP_PER_PULSE 4

enum SeqDirection {
    Paused = 0,
    Forward = 1,
    Backward = -1
};

class Sequencer {

    public:

        Sequencer();
    
        int getTempo() const;
        void setTempo(int tempo);
        void incrTempo();
        void decrTempo();

        int getTrackLen() const;
        void setTrackLen(int len);

        int getStepsPerPulse() const;
        void setStepsPerPulse(int spp);

        int getCurrentStep() const;
        void setCurrentStep(int step, bool reset_time = true);
        
        void update();
        void reset();

        /// @brief Mark recording active, will start at next sequence
        void toggleRecord();
        void setRecord(const bool record);
        bool isRecording() const;
        void feed(Event& e);

        void playPause();
        bool isPaused() const;
        void pause();
        void backward();
        void forward();
        SeqDirection getDirection() const;

        unsigned long usStepLen() const;
        unsigned long usPulseLen() const;

        int eventIndex(int step, const Event& e) const;
        void addEvent(Event e);
        void addEvent(int step, Event e);
        void removeEvent(int step, const Event& e);
        void toggleEvent(int step, Event e);
        void purgeInstrumentEvents(int instrument);
        uint8_t getEventsCount(int step) const;
        uint8_t getEventsCount() const;
        Event* getEvents(int step);
        Event* getEvents();

        bool step_flag = false;
        bool sequence_flag = false;
        bool pulse_flag = false;

    private:

        int _tempo = DEFAULT_TEMPO;
        int _track_len = DEFAULT_TRACK_LEN;
        int _current_step = 0;
        elapsedMicros _elapsed = 0;
        int _date_backup = 0;

        int _steps_per_pulse = DEFAULT_STEP_PER_PULSE;

        bool _record = false;
        bool _record_switch = false;

        SeqDirection _direction = Forward;

        Event _events[MAX_SEQUENCER_STEPS][MAX_EVENTS_PER_STEP];
        uint8_t _events_count[MAX_SEQUENCER_STEPS] = { 0 };
        
};

#endif
