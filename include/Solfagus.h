#ifndef SOLFAGUS_H
#define SOLFAGUS_H

#include <Arduino.h>

enum KeyType {
    Chromatic,
    Major,
    Minor,
    PentatonicMajor,
    PentatonicMinor,
    Blues
};

struct Key {
    int8_t tonic;
    KeyType type;
};

class Solfagus {

    public:

        void setKey(const Key key);
        Key getKey() const;

        void setKeyTonic(const int8_t tonic);
        void setKeyType(const KeyType type);

        /// Note at given degree in the current key
        int8_t noteAt(const int8_t index) const;
    
        int8_t chordNote(const int8_t root_index, const int8_t index) const;
        void chordAt(const int8_t root_index, int8_t notes[], uint8_t n = 4) const;
        void chord(int8_t notes[], uint8_t n = 4) const;

        void majorChord(int8_t notes[], uint8_t n = 4) const;
        void minorChord(int8_t notes[], uint8_t n = 4) const;
        void dimChord(int8_t notes[], uint8_t n = 4) const;
        void dom7Chord(int8_t notes[], uint8_t n = 4) const;

    private:

        Key _key = { 0, Major };

};

#endif