#include "SynthesizerMenu.h"

#include <cmath>

#include "AtomicEnvelopeADSR.h"
#include "AtomicSquareWave.h"
#include "Course0.h"
#include "Event/MenuOpenEvent.h"

const int width = SYNTHESIZER_MENU_ITEM_LENGTH;
const int height = SYNTHESIZER_MENU_ITEM_COUNT;

SynthesizerMenu::SynthesizerMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;

    _waveform = std::make_shared<AtomicWaveSummator>();
    _synth.open();
    _synth.setWaveform(_waveform);
    _synth.start();

    setup(_keyboard.getSize());
    setupMenu();
}

void SynthesizerMenu::setupMenu() {
    _keyboard.setOrigin(_keyboard.getSize() / 2.f);
    float centerX = (float)_target->getSize().x / 2.f;
    float centerY = (float)_target->getSize().y / 2.f;
    _keyboard.setPosition(centerX, centerY);
}

void SynthesizerMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
    _target->draw(_keyboard);
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
            Course0::getInstance()->postEvent(std::make_shared<MenuOpenEvent>());
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

    _keyboard[semitone]->setKeyPressed(true);
    _waveform->addWave(envelope);
    envelope->start();
}

void SynthesizerMenu::removeKeySemitone(char key) {
    size_t semitonePosition = 0;
    if ((semitonePosition = _pressedNotes.find(key)) != std::string::npos) {
        size_t semitone = 0;
        if ((semitone = KEY_NOTES.find(key)) != std::string::npos) {
            _keyboard[semitone]->setKeyPressed(false);
        }
        _pressedNotes.erase(semitonePosition, 1);
        _waveform->stopNthWave(semitonePosition);
    }
}
