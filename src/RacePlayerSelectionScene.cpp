#include "RacePlayerSelectionScene.h"

#include <random>

#include "Course0.h"
#include "Event/MenuOpenEvent.h"
#include "Event/RaceOpenEvent.h"
#include "RacePlayer.hpp"
#include "RaceScene.h"
#include "Scroll.hpp"

RacePlayerSelectionScene::RacePlayerSelectionScene(sf::RenderTarget *target)
        : Scene(target) {
    sf::Vector2u size = _target->getSize();
    _size.x = (float)size.x;
    _size.y = (float)size.y;
    _finishing = false;
    _gen.seed(std::random_device()());

    std::uniform_real_distribution chanceDist(0.f, 1.f), degreesDist(-10.f, 10.f);

    size_t playerCount = sizeof(_players) / sizeof(PlayerOption);
    for (size_t i = 0; i < playerCount; i++) {
        do {
            _players[i].name = generateName();
        } while (_players[i].name.getSize() > 14);
        _players[i].type = chanceDist(_gen) > 0.33f ? PlayerType::BROWN : PlayerType::BLACK;

        _scrolls[i].create(&_players[i]);
        _scrolls[i].setOrigin(_scrolls[i].getSize() / 2.f);
        _scrolls[i].setPosition((2 * i + 1) * _size.x / (2.f * playerCount),
                                _size.y / 2.f);
        _scrolls[i].scale(RACE_PIXEL_SCALE, RACE_PIXEL_SCALE);
        _scrolls[i].rotate(degreesDist(_gen));
        _scrolls[i].setOutlineColor(sf::Color::Black);
    }

    _prevSelectedPlayer = _selectedPlayer = 0;
    moveSelection(0);
}

void RacePlayerSelectionScene::update(sf::Time elapsed) {
}

void RacePlayerSelectionScene::draw(sf::RenderStates states) {
    const size_t scrollCount = sizeof(_scrolls) / sizeof(Scroll);
    for (size_t i = 0; i < scrollCount; i++) {
        if (i == _selectedPlayer)
            continue;
        _target->draw(_scrolls[i]);
    }
    _target->draw(_scrolls[_selectedPlayer]);
}

bool RacePlayerSelectionScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    }
    return true;
}

void RacePlayerSelectionScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    const size_t scrollCount = sizeof(_scrolls) / sizeof(Scroll);

    if (event.code == sf::Keyboard::Escape) {
        _finishing = true;
    } else if (event.code == sf::Keyboard::Enter) {
        Course0::getInstance()->postEvent(
                std::make_shared<RaceOpenEvent>( _players, _selectedPlayer));
    } else if (event.code == sf::Keyboard::Left) {
        moveSelection(-1);
    } else if (event.code == sf::Keyboard::Right) {
        moveSelection(+1);
    }
}

void RacePlayerSelectionScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        Course0::getInstance()->postEvent(std::make_shared<MenuOpenEvent>());
        _finishing = false;
    }
}

sf::String RacePlayerSelectionScene::generateName() {
    size_t nameCount = sizeof(NAMES) / sizeof(sf::String);
    std::uniform_int_distribution dist(0, (int)(nameCount / 2 - 1));

    sf::String name;
    name += NAMES[2 * dist(_gen)];
    name += " ";
    name += NAMES[2 * dist(_gen) + 1];

    return name;
}

void RacePlayerSelectionScene::moveSelection(int diff) {
    const size_t scrollCount = sizeof(_scrolls) / sizeof(Scroll);

    if (diff > 0) {
        if (_selectedPlayer == scrollCount - 1) {
            _selectedPlayer = 0;
        } else {
            _selectedPlayer++;
        }
    } else if (diff < 0) {
        if (_selectedPlayer == 0) {
            _selectedPlayer = scrollCount - 1;
        } else {
            _selectedPlayer--;
        }
    }

    _scrolls[_prevSelectedPlayer].setOutlineColor(sf::Color::Black);
    _scrolls[_selectedPlayer].setOutlineColor(sf::Color(255, 255, 100));
    _prevSelectedPlayer = _selectedPlayer;
}
