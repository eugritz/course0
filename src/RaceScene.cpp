#include "RaceScene.h"

#include <cmath>
#include <iostream>

#include "Course0.h"

RaceScene::RaceScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2u size = _target->getSize();
    _size = sf::Vector2f((float)size.x, (float)size.y);
    _finishing = false;
    setup();
}

void RaceScene::setup() {
    _path.setSize(sf::Vector2f(RACE_TRACK_SIZE_X, RACE_TRACK_SIZE_Y));
    _path.setOrigin(_path.getSize() / 2.f);
    _path.setPosition(_size / 2.f);

    _path.setRoundness(0.5f);
    _path.setIterationCount(50);
    _path.setFillColor(sf::Color::Transparent);
    _path.setOutlineColor(sf::Color::White);
    _path.setOutlineThickness(5.f);
}

bool RaceScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    }
    return true;
}

void RaceScene::update(sf::Time elapsed) {
}

void RaceScene::draw(sf::RenderStates states) {
    _target->draw(_path);
}

void RaceScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Escape) {
        _finishing = true;
    }
}

void RaceScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        Course0::getInstance()->postEvent(MENU_OPEN);
        _finishing = false;
    }
}
