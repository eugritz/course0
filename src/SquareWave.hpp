#pragma once

#include "Waveform.h"

#include <atomic>
#include <cmath>

class SquareWave : public Waveform {
    std::atomic<double> _pitch;
    double _baseOctaveFreq;

public:
    SquareWave() : _baseOctaveFreq(110.0) { }
    SquareWave(double baseOctaveFreq) : _baseOctaveFreq(baseOctaveFreq) { }

    virtual double getSample(int phase, double sampleRate) const {
        if (!_isStarted)
            return 0.0;
        return std::sin(_pitch * (double)phase / sampleRate * 2.0 * M_PI) > 0.0 ?
            0.1 : -0.1;
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
