#include "AtomicSquareWave.h"

#include <cmath>

AtomicSquareWave::AtomicSquareWave() : _baseOctaveFreq(110.0) {
    _phase = 0;
}

AtomicSquareWave::AtomicSquareWave(double baseOctaveFreq)
        : _baseOctaveFreq(baseOctaveFreq) {
    _phase = 0;
}

double AtomicSquareWave::getSample(double sampleRate, PaTime time) {
    if (!_isStarted)
        return 0.0;

    _phase += 1;
    while (_phase >= sampleRate / _pitch)
        _phase -= sampleRate / _pitch;

    double angularVelocity = _pitch * 2.0 * M_PI;
    return std::sin(_phase / sampleRate * angularVelocity) > 0.0 ?
        1.0 : -1.0;
}

void AtomicSquareWave::setSemitone(int nth) {
    double octave12th = std::pow(2.0, 1.0 / 12.0);
    _pitch = _baseOctaveFreq * pow(octave12th, nth);
}

void AtomicSquareWave::setBaseOctaveFrequency(double baseOctaveFreq) {
    _baseOctaveFreq = baseOctaveFreq;
}

void AtomicSquareWave::setPitch(double pitch) {
    _pitch = pitch;
}
