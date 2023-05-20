#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "Waveform.h"

class AtomicWaveSummator : public Waveform {
    std::vector<std::shared_ptr<Waveform>> _waves;
    std::mutex _mutex;

public:
    virtual double getSample(double sampleRate, PaTime time);

    virtual void addWave(std::shared_ptr<Waveform> wave);
    virtual void removeNthWave(size_t nth);
    virtual void stopNthWave(size_t nth);

    const std::shared_ptr<Waveform> operator[](size_t index) const;
    std::shared_ptr<Waveform> &operator[](size_t index);
};
