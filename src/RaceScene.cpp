#include "RaceScene.h"

#include <cmath>

#include "Course0.h"

RaceScene::RaceScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2u size = _target->getSize();
    _size = sf::Vector2f((float)size.x, (float)size.y);
    _finishing = false;
    _playerPosition = 0;
    setup();
}

void RaceScene::setup() {
    _track.setSize(sf::Vector2f(RACE_TRACK_SIZE_X, RACE_TRACK_SIZE_Y));
    _track.setOrigin(_track.getSize() / 2.f);
    _track.setPosition(_size / 2.f);

    _track.setRoundness(RACE_TRACK_ROUNDNESS);
    _track.setIterationCount(RACE_TRACK_ITERATIONS, 120, 0);
    _track.setFillColor(sf::Color::Transparent);
    _track.setOutlineColor(sf::Color::White);
    _track.setOutlineThickness(5.f);

    _player.setFillColor(sf::Color::Red);
    _player.setRadius(10.f);
    _player.setOrigin(_player.getLocalBounds().getSize() / 2.f);
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
    _player.setPosition(_track.getPoint(_playerPosition));
    _playerPosition++;
    if (_playerPosition >= _track.getPointCount())
        _playerPosition = 0;
}

void RaceScene::draw(sf::RenderStates states) {
    _target->draw(_track);
    _target->draw(_player, _track.getTransform());
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
