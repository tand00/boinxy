#include "Solfagus.h"

PROGMEM const int8_t MAJOR_STEPS[] = { 0, 2, 4, 5, 7, 9, 11 };
PROGMEM const int8_t MINOR_STEPS[] = { 0, 2, 3, 5, 7, 8, 10 };
PROGMEM const int8_t PENTA_MAJOR_STEPS[] = { 0, 2, 4, 7, 9 };
PROGMEM const int8_t PENTA_MINOR_STEPS[] = { 0, 3, 5, 7, 10 };
PROGMEM const int8_t BLUES_STEPS[] = { 0, 3, 5, 6, 7, 10 };

PROGMEM const int8_t MAJOR_CHORD_STEPS[] = { 0, 4, 7, 11 };
PROGMEM const int8_t MINOR_CHORD_STEPS[] = { 0, 3, 7, 10 };
PROGMEM const int8_t DIMINISHED_CHORD_STEPS[] = { 0, 3, 6, 9 };
PROGMEM const int8_t DOM7_CHORD_STEPS[] = { 0, 4, 7, 10 };

PROGMEM const double NOTES_TUNING_4[] = {
    261.626,
    277.183,
    293.665,
    311.127,
    329.628,
    349.228,
    369.994,
    391.995,
    415.305,
    440,
    466.164,
    493.883
};

Key Key::basic() const
{
    switch(type) {
        case Major:
        case PentatonicMajor:
        case Chromatic:
            return { tonic, Major };
        case Minor:
        case PentatonicMinor:
        case Blues:
            return { tonic, Minor };
        default:
            return { tonic, Major };
    }
}

void Solfagus::setKey(const Key key)
{
    _key = key;
}

Key Solfagus::getKey() const
{
    return _key;
}

void Solfagus::setKeyTonic(const int8_t tonic)
{
    _key.tonic = tonic;
}

void Solfagus::setKeyType(const KeyType type)
{
    _key.type = type;
}

int8_t Solfagus::noteAtIndex(const Key& scale, const int8_t index)
{
    switch(scale.type) {
        case Chromatic:
            return scale.tonic + index;
        case Major:
            return scale.tonic + MAJOR_STEPS[index % 7] + 12 * (index / 7);
        case Minor:
            return scale.tonic + MINOR_STEPS[index % 7] + 12 * (index / 7);
        case PentatonicMajor:
            return scale.tonic + PENTA_MAJOR_STEPS[index % 5] + 12 * (index * 5);
        case PentatonicMinor:
            return scale.tonic + PENTA_MINOR_STEPS[index % 5] + 12 * (index * 5);
        case Blues:
            return scale.tonic + BLUES_STEPS[index % 6] + 12 * (index * 6);
    }
}

int8_t Solfagus::noteAt(const int8_t index) const
{
    return noteAtIndex(_key, index);
}

int8_t Solfagus::chordNote(const int8_t root_index, const int8_t index) const
{
    switch(_key.type) {
        case Major:
        case Minor:
            return noteAt(root_index + index * 2);
        case PentatonicMajor:
            return noteAtIndex(_key.basic(), root_index);
        case PentatonicMinor:
        default:
            return root_index;
    }
}

void Solfagus::chordAt(const int8_t root_index, int8_t notes[], uint8_t n) const
{
    for(int i = 1 ; i < n ; i++) {
        notes[i] = chordNote(root_index, i);
    }
}

void Solfagus::chord(int8_t notes[], uint8_t n) const
{
    const int8_t root = notes[0] % 12;
    const int8_t octave = notes[0] / 12;

    int8_t index = 0;
    int8_t note = _key.tonic;
    while(note != _key.tonic || index == 0) {
        if(note % 12 == root) {
            chordAt(index, notes, n);
            return;
        }
        index++;
        note = noteAt(index);
    }
    chordAt(0, notes, n);
}

void Solfagus::majorChord(int8_t notes[], uint8_t n) const
{
    for(int i = 1 ; i < n ; i++) {
        notes[i] = notes[0] + MAJOR_CHORD_STEPS[i];
    }
}

void Solfagus::minorChord(int8_t notes[], uint8_t n) const
{
    for(int i = 1 ; i < n ; i++) {
        notes[i] = notes[0] + MINOR_CHORD_STEPS[i];
    }
}

void Solfagus::dimChord(int8_t notes[], uint8_t n) const
{
    for(int i = 1 ; i < n ; i++) {
        notes[i] = notes[0] + DIMINISHED_CHORD_STEPS[i];
    }
}

void Solfagus::dom7Chord(int8_t notes[], uint8_t n) const
{
    for(int i = 1 ; i < n ; i++) {
        notes[i] = notes[0] + DOM7_CHORD_STEPS[i];
    }
}

double Solfagus::noteFrequency(int8_t note)
{
    int8_t octave = note / 12;
    int8_t base = note % 12;
    double mult = pow(2, octave - 4);
    return NOTES_TUNING_4[base] * mult;
}
