#include <Sequencer.h>

unsigned int Sequencer::getTempo() const
{
    return _tempo;
}

void Sequencer::setTempo(unsigned int tempo)
{
    _tempo = max(1, tempo);
}

void Sequencer::incrTempo()
{
    setTempo(_tempo + 1);
}

void Sequencer::decrTempo()
{
    setTempo(_tempo - 1);
}

unsigned int Sequencer::getTrackLen() const
{
    return _track_len;
}

unsigned int Sequencer::getCurrentStep() const
{
    return _current_step;
}

void Sequencer::setTrackLen(unsigned int len)
{
    _track_len = min(max(1, len), MAX_SEQUENCER_STEPS);
}

void Sequencer::setCurrentStep(unsigned int step, bool reset_time)
{
    _current_step = step;
    if(reset_time) _elapsed = 0;
}

void Sequencer::update()
{
    step_flag = false;
    if(_direction == Paused) return;
    unsigned long step_len = usStepLen();
    if(_elapsed >= step_len) {
        _current_step = (_current_step + _direction * 1) % _track_len;
        _elapsed -= step_len;
        step_flag = true;
        triggerStep();
    }
}

void Sequencer::triggerStep()
{
    // TODO
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
    triggerStep();
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
    double beat_duration = (60.0 / ((double) _tempo)) * 1.0E6;
    return beat_duration;
}
