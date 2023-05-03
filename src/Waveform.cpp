#include "Waveform.h"

void Waveform::start() {
    _isStarted = true;
}

bool Waveform::isStarted() {
    return _isStarted;
}

void Waveform::stop() {
    _isStarted = false;
}

void Waveform::setStream(PaStream *stream) {
    _stream = stream;
    _isStarted = false;
}
