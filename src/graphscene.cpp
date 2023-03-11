#include "graphscene.h"

#include "project0.h"

GraphScene::GraphScene(sf::RenderTarget *target) : Scene(target) { }

void GraphScene::update(sf::Time elapsed) {
}

void GraphScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color::White);
}

bool GraphScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter ||
            event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Space) {
            _finishing = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Project0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}
