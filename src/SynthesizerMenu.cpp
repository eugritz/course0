#include "SynthesizerMenu.h"

#include "Course0.h"

const int width = SYNTHESIZER_MENU_ITEM_LENGTH;
const int height = SYNTHESIZER_MENU_ITEM_COUNT;

SynthesizerMenu::SynthesizerMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    
    setup(width, height);
    setupMenu();
}

SynthesizerMenu::~SynthesizerMenu() {
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
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Course0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}
