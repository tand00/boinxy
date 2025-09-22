#include <Sequencer.h>

Sequencer::Sequencer()
{ }

int Sequencer::getTempo() const
{
    return _tempo;
}

void Sequencer::setTempo(int tempo)
{
    _tempo = min(max(1, tempo), 300);
}

void Sequencer::incrTempo()
{
    setTempo(_tempo + 1);
}

void Sequencer::decrTempo()
{
    setTempo(_tempo - 1);
}

int Sequencer::getTrackLen() const
{
    return _track_len;
}

int Sequencer::getCurrentStep() const
{
    return _current_step;
}

void Sequencer::setTrackLen(int len)
{
    _track_len = min(max(1, len), MAX_SEQUENCER_STEPS);
}

int Sequencer::getStepsPerPulse() const
{
    return _steps_per_pulse;
}

void Sequencer::setStepsPerPulse(int spp)
{
    _steps_per_pulse = spp;
}

void Sequencer::setCurrentStep(int step, bool reset_time)
{
    _current_step = step;
    if(reset_time) _elapsed = 0;
}

int Sequencer::getCurrentPulse() const
{
    return (getCurrentStep() / getStepsPerPulse());
}

int Sequencer::getPreviousStep() const
{
    return (_current_step + _track_len - 1) % _track_len;
}

void Sequencer::update()
{
    step_flag = false;
    sequence_flag = false;
    pulse_flag = false;
    if(_direction == Paused) return;
    unsigned long step_len = usStepLen();
    if(_elapsed >= step_len) {
        _current_step = (_current_step + _direction) % _track_len;
        if(_current_step < 0) _current_step += _track_len;
        _elapsed -= step_len;
        step_flag = true;
        sequence_flag = _current_step == 0;
        if(_current_step % _steps_per_pulse == 0) pulse_flag = true;
        if(sequence_flag && auto_stop_record && _recorded_events && isRecording()) {
            setRecord(false);
        }
    }
}

void Sequencer::toggleRecord()
{
    setRecord(!_record);
}

void Sequencer::setRecord(const bool record)
{
    if(_record != record) {
        _record = record;
        _recorded_events = false;
        if(_record) {
            int current = getCurrentStep();
            for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
                if(_active_events[i].isNone()) continue;
                addEvent(current, _active_events[i].on());
            }
        } else {
            int previous = getPreviousStep();
            for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
                if(_active_events[i].isNone()) continue;
                addEvent(previous, _active_events[i].off());
                // _active_events[i].nonify();
            }
        }
    }
}

bool Sequencer::isRecording() const
{
    return _record;
}

void Sequencer::feed(Event& e)
{
    updateActiveEvents(e);
    if(_record) {
        int step = getCurrentStep();
        if(e.type == NoteOff && 8 * _elapsed > 7 * usStepLen()) {
            step = (step + _track_len - 1) % _track_len;
        } else if(e.type == NoteOn && 8 * _elapsed > 7 * usStepLen()) {
            step = (step + 1) % _track_len;
        }
        addEvent(step, e);
        _recorded_events = true;
    }
}

void Sequencer::reset()
{
    _current_step = 0;
    _elapsed = 0;
    step_flag = true;
    sequence_flag = true;
}

void Sequencer::playPause()
{
    if(isPaused()) forward();
    else pause();
}

bool Sequencer::isPaused() const
{
    return _direction == Paused;
}

void Sequencer::pause()
{
    _date_backup = _elapsed;
    _direction = Paused;
}

void Sequencer::backward()
{
    if(_direction == Paused) _elapsed = _date_backup;
    _direction = Backward;
}

void Sequencer::forward()
{
    if(_direction == Paused) _elapsed = _date_backup;
    _direction = Forward;
}

SeqDirection Sequencer::getDirection() const 
{
    return _direction;
}

unsigned long Sequencer::usStepLen() const
{
    double beat_duration = (60.0 / ((double) _tempo * _steps_per_pulse)) * 1.0E6;
    return beat_duration;
}

unsigned long Sequencer::usPulseLen() const
{
    double pulse_duration = (60.0 / ((double) _tempo)) * 1.0E6;
    return pulse_duration;
}

int Sequencer::eventIndex(int step, const Event &e) const
{
    for(int i = 0 ; i < MAX_EVENTS_PER_STEP ; i++) {
        if(_events[step][i] == e) {
            return i;
        }
    }
    return -1;
}

void Sequencer::addEvent(Event e)
{
    addEvent(getCurrentStep(), e);
}

void Sequencer::addEvent(int step, Event e)
{
    if(eventIndex(step, e) >= 0) return;
    int index = findFreeEventIndex(step);
    if(index == -1) return;
    _events[step][index] = e;
}

void Sequencer::removeEvent(int step, const Event &e)
{
    int to_remove = eventIndex(step, e);
    if(to_remove == -1) return;
    _events[step][to_remove].nonify();
}

void Sequencer::toggleEvent(int step, Event e)
{
    int to_remove = eventIndex(step, e);
    if(to_remove >= 0) {
        _events[step][to_remove].nonify();
    } else {
        int index = findFreeEventIndex(step);
        if(index == -1) return;
        _events[step][index] = e;
    }
}

void Sequencer::purgeInstrument(int instrument)
{
    for(int step = 0 ; step < _track_len ; step++) {
        purgeInstrumentStep(step, instrument);
    }
}

void Sequencer::purgeInstrumentStep(int step, int instrument)
{
    for(int i = 0 ; i < MAX_EVENTS_PER_STEP ; i++) {
        if(_events[step][i].instrument == instrument) {
            _events[step][i].nonify();
        }
    }
}

Event *Sequencer::getEvents(int step)
{
    return _events[step];
}

Event *Sequencer::getEvents()
{
    return _events[getCurrentStep()];
}

Event *Sequencer::getPreviousEvents()
{
    return _events[getPreviousStep()];
}

Event *Sequencer::getActiveEvents()
{
    return _active_events;
}

int Sequencer::findFreeEventIndex(int step)
{
    for(int i = 0 ; i < MAX_EVENTS_PER_STEP ; i++) {
        if(_events[step][i].isNone()) return i;
    }
    return -1;
}

bool Sequencer::updateActiveEvents(Event e)
{
    if(e.type == NoteOn) {
        for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
            if(_active_events[i].isNone()) {
                _active_events[i] = e;
                return true;
            }
        }
        Serial.println("! Reached maximum number of ON events !");
        return false;
    } else if(e.type == NoteOff) {
        for(int i = 0 ; i < MAX_ACTIVE_EVENTS ; i++) {
            if(e.isSameAction(_active_events[i])) {
                _active_events[i].nonify();
            }
        }
        return true;
    }
    return true;
}
