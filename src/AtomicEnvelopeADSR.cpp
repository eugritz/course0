#include "AtomicEnvelopeADSR.h"

AtomicEnvelopeADSR::AtomicEnvelopeADSR(std::shared_ptr<Waveform> waveform) {
    _waveform = waveform;

    _attackDuration = 0.1;
    _decayDuration = 0.1;
    _releaseDuration = 0.1;
    _attackAmplitude = 1.0;
    _sustainAmplitude = 0.8;

    _startTime = 0.0;
    _endTime = 0.0;
}

double AtomicEnvelopeADSR::getSample(double sampleRate, PaTime time) {
    double amplitude = 0.0;
    PaTime lifeTime = time - _startTime;

    if (_isStarted) {
        if (lifeTime <= _attackDuration) {
            double attack = lifeTime / _attackDuration;
            amplitude = attack * _attackAmplitude;
        } else if (lifeTime - _attackDuration <= _decayDuration) {
            double decay = (lifeTime - _attackDuration) / _decayDuration;
            double step = _sustainAmplitude - _attackAmplitude;
            amplitude = _attackAmplitude + decay * step;
        } else {
            amplitude = _sustainAmplitude;
        }
    } else {
        double release = (time - _endTime) / _releaseDuration;
        amplitude = _sustainAmplitude - _sustainAmplitude * release;
    }

    if (amplitude <= 0.0001)
        return 0.0;
    return amplitude * _waveform->getSample(sampleRate, time);
}

void AtomicEnvelopeADSR::start() {
    if (_isStarted)
        return;
    Waveform::start();
    _waveform->start();
    _startTime = Pa_GetStreamTime(_stream);
}

void AtomicEnvelopeADSR::stop() {
    if (!_isStarted)
        return;
    Waveform::stop();
    _endTime = Pa_GetStreamTime(_stream);
}

void AtomicEnvelopeADSR::setStream(PaStream *stream) {
    Waveform::setStream(stream);
    _waveform->setStream(stream);
}

void AtomicEnvelopeADSR::setAttackDuration(double durationSeconds) {
    _attackDuration = durationSeconds;
}

void AtomicEnvelopeADSR::setDecayDuration(double durationSeconds) {
    _decayDuration = durationSeconds;
}

void AtomicEnvelopeADSR::setReleaseDuration(double durationSeconds) {
    _releaseDuration = durationSeconds;
}

void AtomicEnvelopeADSR::setAttackAmplitude(double amplitude) {
    _attackAmplitude = amplitude;
}

void AtomicEnvelopeADSR::setSustainAmplitude(double amplitude) {
    _sustainAmplitude = amplitude;
}
