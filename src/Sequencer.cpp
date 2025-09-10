#include <Sequencer.h>

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
        if(_current_step == 0) sequence_flag = true;
        if(_current_step % _steps_per_pulse == 0) pulse_flag = true;
    }
}

void Sequencer::toggleRecord()
{
    _record = !_record;
}

void Sequencer::setRecord(const bool record)
{
    _record = record;
}

bool Sequencer::isRecording() const
{
    return _record;
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

unsigned long Sequencer::usStepLen()
{
    double beat_duration = (60.0 / ((double) _tempo * _steps_per_pulse)) * 1.0E6;
    return beat_duration;
}

int Sequencer::eventIndex(int step, const Event &e) const
{
    for(int i = 0 ; i < _events_count[step] ; i++) {
        if(_events[step][i] == e) {
            return i;
        }
    }
    return -1;
}

void Sequencer::addEvent(int step, Event e)
{
    if(eventIndex(step, e) >= 0) return;
    int n_events = getEventsCount(step);
    if(n_events == MAX_EVENTS_PER_STEP) return;
    _events[step][n_events] = e;
    _events_count[step]++;
}

void Sequencer::removeEvent(int step, const Event &e)
{
    int to_remove = eventIndex(step, e);
    int n_events = getEventsCount(step);
    if(to_remove == -1) return;
    for(int i = to_remove ; i < n_events - 1 ; i++) {
        _events[step][i] = _events[step][i + 1];
    }
    _events_count[step]--;
}

uint8_t Sequencer::getEventsCount(int step) const
{
    return _events_count[step];
}

uint8_t Sequencer::getEventsCount() const
{
    return _events_count[getCurrentStep()];
}

void Sequencer::toggleEvent(int step, Event e)
{
    int to_remove = eventIndex(step, e);
    int n_events = getEventsCount(step);
    if(to_remove >= 0) {
        for(int i = to_remove ; i < n_events - 1 ; i++) {
            _events[step][i] = _events[step][i + 1];
        }
        _events_count[step]--;
    } else {
        if(n_events == MAX_EVENTS_PER_STEP) return;
        _events[step][n_events] = e;
        _events_count[step]++;
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
