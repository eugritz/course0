#pragma once

#include <atomic>

#include "Waveform.h"

class AtomicSquareWave : public Waveform {
    int _phase;
    std::atomic<double> _pitch;
    std::atomic<double> _baseOctaveFreq;

public:
    AtomicSquareWave();
    AtomicSquareWave(double baseOctaveFreq);

    virtual double getSample(double sampleRate, PaTime time);

    void setSemitone(int nth);
    void setBaseOctaveFrequency(double baseOctaveFreq);
    void setPitch(double pitch);
};
