#include "RaceScene.h"

#include <algorithm>
#include <cmath>

#include "Course0.h"

const int LEVEL[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
};

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
    _track.setIterationCount(RACE_TRACK_ITERATIONS, true);
    _track.setFillColor(sf::Color::Transparent);
    _track.setOutlineColor(sf::Color::White);
    _track.setOutlineThickness(5.f);

    _player.setFillColor(sf::Color::Red);
    _player.setRadius(10.f);
    _player.setOrigin(_player.getLocalBounds().getSize() / 2.f);

    _map.load("race-tileset.png", sf::Vector2u(32, 32), LEVEL, 16, 8);
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
    // _target->draw(_map);
    // RectangleShape2 rect(sf::Vector2f(300.f, 200.f), 50, 0.2f, true);
    // rect.setPosition(20.f, 20.f);
    // _target->draw(rect);
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
