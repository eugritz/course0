#pragma once

#include <atomic>
#include <cmath>

#include "Waveform.h"

class AtomicSquareWave : public Waveform {
    int _phase;
    std::atomic<double> _pitch;
    std::atomic<double> _baseOctaveFreq;

public:
    AtomicSquareWave() : _baseOctaveFreq(110.0) {
        _phase = 0;
    }

    AtomicSquareWave(double baseOctaveFreq) : _baseOctaveFreq(baseOctaveFreq) {
        _phase = 0;
    }

    virtual double getSample(double sampleRate, PaTime time) {
        if (!_isStarted)
            return 0.0;

        _phase += 1;
        while (_phase >= sampleRate / _pitch)
            _phase -= sampleRate / _pitch;

        double angularVelocity = _pitch * 2.0 * M_PI;
        return std::sin(_phase / sampleRate * angularVelocity) > 0.0 ?
            1.0 : -1.0;
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
