#include <SampleLibrary.h>

#include <Audio.h>

void SampleLibrary::setup()
{
    if(!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("Unable to initialize SD card !");
    }
    _root = SD.open(SAMPLES_PATH);
    _n_categories = countDirectory(_root);
    _category = _root.openNextFile();
    _category_index = 0;
    openCategory();
    Serial.println("Initialized samples library !");
    Serial.println(String(" - Found ") + _n_categories + " categories");
}

void SampleLibrary::reset()
{
    AudioNoInterrupts();
    _sample.close();
    _category.close();
    _category = _root.openNextFile();
    _category_index = 0;
    openCategory();
    AudioInterrupts();
}

void SampleLibrary::nextCategory()
{
    AudioNoInterrupts();
    _sample.close();
    _category = _root.openNextFile();
    _category_index++;
    if(!_category) {
        _root.rewindDirectory();
        _category = _root.openNextFile();
        _category_index = 0;
    }
    openCategory();
    AudioInterrupts();
}

void SampleLibrary::previousCategory()
{
    AudioNoInterrupts();
    _sample.close();
    _category.close();
    uint16_t target = (_category_index == 0) ? (_n_categories - 1) : (_category_index - 1);
    _category = openFileN(_root, target);
    _category_index = target;
    openCategory();
    AudioInterrupts();
}

uint16_t SampleLibrary::categoryIndex() const
{
    return _category_index;
}

void SampleLibrary::nextSample()
{
    AudioNoInterrupts();
    _sample = _category.openNextFile();
    _sample_index++;
    if(!_sample) {
        _category.rewindDirectory();
        _sample = _category.openNextFile();
        _sample_index = 0;
    }
    AudioInterrupts();
}

void SampleLibrary::previousSample()
{
    AudioNoInterrupts();
    _sample.close();
    uint16_t target = (_sample_index == 0) ? (_n_samples - 1) : (_sample_index - 1);
    _sample = openFileN(_category, target);
    _sample_index = target;
    AudioInterrupts();
}

uint16_t SampleLibrary::sampleIndex() const
{
    return _sample_index;
}

uint32_t SampleLibrary::globalIndex() const
{
    uint32_t index = _category_index;
    index <<= 16;
    index |= _sample_index;
}

File *SampleLibrary::getCategory()
{
    return &_category;
}

File *SampleLibrary::getSample()
{
    return &_sample;
}

String SampleLibrary::getPath()
{
    return String(SAMPLES_PATH) + "/" + _category.name() + "/" + _sample.name();
}

String SampleLibrary::getSampleAt(const uint32_t i)
{
    uint16_t sample_i = i & 0xFF;
    uint16_t cat_i = (i >> 16) & 0xFF;
    return getSampleAt(cat_i, sample_i);
}

String SampleLibrary::getSampleAt(const uint16_t cat_i, const uint16_t sample_i)
{
    File category = openFileN(_root, cat_i);
    File sample = openFileN(category, sample_i);
    return String(SAMPLES_PATH) + "/" + category.name() + "/" + sample.name();
}

uint16_t SampleLibrary::countDirectory(File &dir)
{
    uint16_t res = 0;
    File entry = dir.openNextFile();
    while(entry) {
        res++;
        entry = dir.openNextFile();
    }
    entry.close();
    dir.rewindDirectory();
    return res;
}

void SampleLibrary::openCategory()
{
    if(!_category.isDirectory()) {
        return;
    }
    _n_samples = countDirectory(_category);
    _sample = _category.openNextFile();
    _sample_index = 0;
}

File SampleLibrary::openFileN(File &dir, const uint16_t n)
{
    dir.rewindDirectory();
    File entry = dir.openNextFile();
    for(uint16_t i = 0 ; i < n ; i++) {
        entry = dir.openNextFile();
        if(!entry) {
            dir.rewindDirectory();
            entry = dir.openNextFile();
        }
    }
    return entry;
}
