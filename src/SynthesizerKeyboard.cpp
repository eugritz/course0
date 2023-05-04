#include "SynthesizerKeyboard.h"

SynthesizerKeyboard::SynthesizerKeyboard() {
    if (!_keyFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
        return;
    }
    _keyFont.setSmooth(true);
    _last = 0;

    setupKeys();
}

void SynthesizerKeyboard::setupKeys() {
    std::shared_ptr<PianoKey> prev = addWhiteKey("C");
    prev = addBlackKey("C#", prev);
    prev = addWhiteKey("D", prev);
    prev = addBlackKey("D#", prev);
    prev = addWhiteKey("E", prev);
    prev = addWhiteKey("F", prev);
    prev = addBlackKey("F#", prev);
    prev = addWhiteKey("G", prev);
    prev = addBlackKey("G#", prev);
    prev = addWhiteKey("A", prev);
    prev = addBlackKey("A#", prev);
    prev = addWhiteKey("B", prev);
    prev = addWhiteKey("C", prev);
}

void SynthesizerKeyboard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto it = _whiteKeys.begin(); it != _whiteKeys.end(); it++) {
        target.draw(**it, states);
    }
    for (auto it = _blackKeys.begin(); it != _blackKeys.end(); it++) {
        target.draw(**it, states);
    }
}

sf::Vector2f SynthesizerKeyboard::getSize() const {
    const std::shared_ptr<PianoKey> last = _whiteKeys.back();
    return {
        last->getPosition().x + last->getSize().x,
        last->getSize().y
    };
}

const std::shared_ptr<PianoKey> SynthesizerKeyboard::operator[](size_t index) const {
    return _mappings.at(index);
}

std::shared_ptr<PianoKey> SynthesizerKeyboard::operator[](size_t index) {
    return _mappings.at(index);
}

std::shared_ptr<PianoKey> SynthesizerKeyboard::addWhiteKey(const sf::String &note) {
    auto key = std::make_shared<WhitePianoKey>(_keyFont, note);
    key->setPosition(0, 0);
    _whiteKeys.push_back(key);

    _mappings[_last++] = key;
    return _whiteKeys.back();
}

std::shared_ptr<PianoKey> SynthesizerKeyboard::addWhiteKey(
        const sf::String &note, std::shared_ptr<PianoKey> previous) {
    auto key = std::make_shared<WhitePianoKey>(_keyFont, note);
    key->setPosition(previous->getPosition().x + previous->getSize().x, 0);
    _whiteKeys.push_back(key);

    _mappings[_last++] = key;
    return _whiteKeys.back();
}

std::shared_ptr<PianoKey> SynthesizerKeyboard::addBlackKey(
        const sf::String &note, std::shared_ptr<PianoKey> previous) {
    auto key = std::make_shared<BlackPianoKey>(_keyFont, note);
    key->setOrigin(key->getSize().x / 2.f, 0);
    key->setPosition(previous->getPosition().x + previous->getSize().x, 0);
    _blackKeys.push_back(key);

    _mappings[_last++] = key;
    return _whiteKeys.back();
}
