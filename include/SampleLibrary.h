#ifndef SAMPLE_LIBRARY_H
#define SAMPLE_LIBRARY_H

#include <Arduino.h>
#include <SD.h>

#define SAMPLES_PATH "/samples"

class SampleLibrary {

    public:

        void setup();

        void reset();

        void nextCategory();
        void previousCategory();
        uint16_t categoryIndex() const;

        void nextSample();
        void previousSample();
        uint16_t sampleIndex() const;

        uint32_t globalIndex() const;

        File* getCategory();
        File* getSample();

        String getPath();

        String getSampleAt(const uint32_t i);
        String getSampleAt(const uint16_t cat_i, const uint16_t sample_i);

    private:

        uint16_t countDirectory(File& dir);
        void openCategory();
        File openFileN(File& dir, const uint16_t n);

        File _root;
        File _category;
        File _sample;
        uint16_t _category_index = 0;
        uint16_t _sample_index = 0;
        uint16_t _n_categories;
        uint16_t _n_samples;

};

#endif