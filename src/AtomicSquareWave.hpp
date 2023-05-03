#pragma once

#include <atomic>
#include <cmath>

#include "Waveform.h"

class AtomicSquareWave : public Waveform {
    std::atomic<double> _pitch;
    std::atomic<double> _baseOctaveFreq;

public:
    AtomicSquareWave() : _baseOctaveFreq(110.0) { }
    AtomicSquareWave(double baseOctaveFreq) : _baseOctaveFreq(baseOctaveFreq) { }

    virtual double getSample(double sampleRate, PaTime time, int phase) const {
        if (!_isStarted)
            return 0.0;
        double angularVelocity = _pitch * 2.0 * M_PI;
        return std::sin(time / sampleRate * angularVelocity) > 0.0 ?
            1.0 : -1.0;
    }

    virtual double getFrequency() const {
        return _pitch;
    }

    void setSemitone(int nth) {
        double octave12th = std::pow(2.0, 1.0 / 12.0);
        _pitch = _baseOctaveFreq * pow(octave12th, nth);
    }

    void setBaseOctaveFrequency(double baseOctaveFreq) {
        _baseOctaveFreq = baseOctaveFreq;
    }

    void setPitch(double pitch) {
        _pitch = pitch;
    }
};
