#include "SynthesizerMenu.h"

#include <iostream>
#include <string>

#include "AtomicEnvelopeADSR.hpp"
#include "AtomicSquareWave.hpp"
#include "AtomicWaveSummator.hpp"
#include "Course0.h"

const int width = SYNTHESIZER_MENU_ITEM_LENGTH;
const int height = SYNTHESIZER_MENU_ITEM_COUNT;

SynthesizerMenu::SynthesizerMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;

    _waveform = std::make_shared<AtomicWaveSummator>();
    _synth.open();
    _synth.setWaveform(_waveform);
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
    double octave12th = std::pow(2.0, 1.0 / 12.0);
    double pitch = 130.81 * pow(octave12th, semitone);

    auto wave = std::make_shared<AtomicSquareWave>();
    wave->setPitch(pitch);
    auto envelope = std::make_shared<AtomicEnvelopeADSR>(wave);
    envelope->setReleaseDuration(0.8);
    envelope->setAttackAmplitude(0.1);
    envelope->setSustainAmplitude(0.08);

    _waveform->addWave(envelope);
    envelope->start();
}

void SynthesizerMenu::removeKeySemitone(char key) {
    size_t semitonePosition = 0;
    if ((semitonePosition = _pressedNotes.find(key)) != std::string::npos) {
        _pressedNotes.erase(semitonePosition, 1);
        _waveform->stopNthWave(semitonePosition);
    }
}
