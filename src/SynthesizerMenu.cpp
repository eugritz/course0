#include "SynthesizerMenu.h"

#include <iostream>
#include <string>

#include "Course0.h"

const int width = SYNTHESIZER_MENU_ITEM_LENGTH;
const int height = SYNTHESIZER_MENU_ITEM_COUNT;

SynthesizerMenu::SynthesizerMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;

    _waveform = std::make_shared<AtomicSquareWave>(130.81);
    _envelope = std::make_shared<AtomicEnvelopeADSR>(_waveform);
    _envelope->setReleaseDuration(0.8);
    _envelope->setAttackAmplitude(0.1);
    _envelope->setSustainAmplitude(0.08);

    _synth.open();
    _synth.setWaveform(_envelope);
    _synth.start();

    setup(width, height);
    setupMenu();
}

void SynthesizerMenu::setupMenu() {
}

void SynthesizerMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool SynthesizerMenu::handleEvent(const sf::Event &event) {
    if (!MenuScene::handleEvent(event))
        return true;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter ||
            event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Space) {
            _finishing = true;
        } else {
            onKeyPressed(event.key);
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Course0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        } else {
            onKeyReleased(event.key);
        }
    }
    return true;
}

void SynthesizerMenu::onKeyPressed(const sf::Event::KeyEvent &event) {
    sf::String keyDescription = sf::Keyboard::getDescription(event.scancode);
    if (keyDescription.getSize() != 1)
        return;

    char key = keyDescription[0];
    addKeySemitone(key);
}

void SynthesizerMenu::onKeyReleased(const sf::Event::KeyEvent &event) {
    sf::String keyDescription = sf::Keyboard::getDescription(event.scancode);
    if (keyDescription.getSize() != 1)
        return;

    wchar_t key = keyDescription[0];
    removeKeySemitone(key);
}

void SynthesizerMenu::addKeySemitone(char key) {
    int semitone = 0;
    if ((semitone = KEY_NOTES.find(key)) == std::string::npos ||
        _pressedNotes.find(key) != std::string::npos) {
        return;
    }

    _pressedNotes += key;
    _envelope->start();
    _waveform->setSemitone(semitone);
}

void SynthesizerMenu::removeKeySemitone(char key) {
    int semitone = 0;

    size_t semitonePosition = 0;
    if ((semitonePosition = _pressedNotes.find(key)) != std::string::npos)
        _pressedNotes.erase(semitonePosition, 1);
    if (_pressedNotes.getSize() == 0) {
        _envelope->stop();
        return;
    }

    char last = _pressedNotes[_pressedNotes.getSize() - 1];
    if ((semitone = KEY_NOTES.find(last)) == std::string::npos)
        return;
    _waveform->setSemitone(semitone);
}
