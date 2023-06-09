#include "AtomicWaveSummator.h"

double AtomicWaveSummator::getSample(double sampleRate, PaTime time) {
    std::unique_lock lock(_mutex);

    double mixed = 0.0;
    size_t i = 0;

    while (i < _waves.size()) {
        auto &wave = _waves[i];

        double sample = wave->getSample(sampleRate, time);
        if (sample == 0.0 && !wave->isStarted()) {
            _waves.erase(_waves.begin() + i);
        } else {
            mixed += sample;
        }

        i++;
    }

    return mixed;
}

void AtomicWaveSummator::addWave(std::shared_ptr<Waveform> wave) {
    std::unique_lock lock(_mutex);
    wave->setStream(_stream);
    _waves.push_back(wave);
}

void AtomicWaveSummator::removeNthWave(size_t nth) {
    std::unique_lock lock(_mutex);
    _waves.erase(_waves.begin() + nth);
}

void AtomicWaveSummator::stopNthWave(size_t nth) {
    std::unique_lock lock(_mutex);

    size_t startedCount = 0;
    size_t stoppedCount = 0;

    for (auto it = _waves.begin(); it != _waves.end(); it++) {
        if ((*it)->isStarted()) {
            startedCount++;
        } else {
            stoppedCount++;
        }

        if (startedCount > nth)
            break;
    }

    if (startedCount > 0)
        _waves[stoppedCount + startedCount - 1]->stop();
}

const std::shared_ptr<Waveform> AtomicWaveSummator::operator[](size_t index) const {
    return _waves[index];
}

std::shared_ptr<Waveform> &AtomicWaveSummator::operator[](size_t index) {
    return _waves[index];
}
