#include "Solfagus.h"

PROGMEM const char MAJOR_STEPS[] = { 0, 2, 4, 5, 7, 9, 11 };
PROGMEM const char MINOR_STEPS[] = { 0, 2, 3, 5, 7, 8, 10 };
PROGMEM const char PENTA_MAJOR_STEPS[] = { 0, 2, 4, 7, 9 };
PROGMEM const char PENTA_MINOR_STEPS[] = { 0, 3, 5, 7, 10 };
PROGMEM const char BLUES_STEPS[] = { 0, 3, 5, 6, 7, 10 };

PROGMEM const char MAJOR_CHORD_STEPS[] = { 0, 4, 7, 11 };
PROGMEM const char MINOR_CHORD_STEPS[] = { 0, 3, 7, 10 };
PROGMEM const char DIMINISHED_CHORD_STEPS[] = { 0, 3, 6, 9 };
PROGMEM const char DOM7_CHORD_STEPS[] = { 0, 4, 7, 10 };

PROGMEM const char* MAJOR_SCALE_CHORDS[] = { MAJOR_CHORD_STEPS, MINOR_CHORD_STEPS, MINOR_CHORD_STEPS, MAJOR_CHORD_STEPS, MAJOR_CHORD_STEPS, MINOR_CHORD_STEPS, DIMINISHED_CHORD_STEPS };
PROGMEM const char* MINOR_SCALE_CHORDS[] = { MINOR_CHORD_STEPS, DIMINISHED_CHORD_STEPS, MAJOR_CHORD_STEPS, MINOR_CHORD_STEPS, MINOR_CHORD_STEPS, MAJOR_CHORD_STEPS, MAJOR_CHORD_STEPS };

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

int8_t Solfagus::noteAt(const int8_t index) const
{
    switch(_key.type) {
        case Chromatic:
            return _key.tonic + (index % 12);
        case Major:
            return _key.tonic + MAJOR_STEPS[index % 7];
        case Minor:
            return _key.tonic + MINOR_STEPS[index % 7];
        case PentatonicMajor:
            return _key.tonic + PENTA_MAJOR_STEPS[index % 5];
        case PentatonicMinor:
            return _key.tonic + PENTA_MINOR_STEPS[index % 5];
        case Blues:
            return _key.tonic + BLUES_STEPS[index % 6];
    }
}

int8_t Solfagus::chordNote(const int8_t root_index, const int8_t index) const
{
    switch(_key.type) {
        case Chromatic:
        case Major:
        case PentatonicMajor:
            return MAJOR_SCALE_CHORDS[root_index][index];
        case Minor:
        case PentatonicMinor:
        case Blues:
            return MINOR_SCALE_CHORDS[root_index][index];
    }
}
