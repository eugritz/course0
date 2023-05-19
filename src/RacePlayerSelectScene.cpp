#include "RacePlayerSelectScene.h"

#include <algorithm>
#include <random>

#include "Course0.h"
#include "GameEvent.hpp"
#include "RacePlayer.hpp"
#include "RaceScene.h"
#include "Resources.hpp"
#include "Scroll.hpp"

RacePlayerSelectScene::RacePlayerSelectScene(sf::RenderTarget *target)
        : Scene(target) {
    _finishing = false;
    gen.seed(std::random_device()());

    sf::String name;
    do {
        name = generateName();
    } while (name.getSize() > 14);

    _scroll.create(name, BROWN);
    _scroll.scale(RACE_PIXEL_SCALE, RACE_PIXEL_SCALE);
    _scroll.setOutlineColor(sf::Color(255, 255, 100));
}

void RacePlayerSelectScene::update(sf::Time elapsed) {
}

void RacePlayerSelectScene::draw(sf::RenderStates states) {
    _target->draw(_scroll);
}

bool RacePlayerSelectScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    }
    return true;
}

void RacePlayerSelectScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Escape) {
        _finishing = true;
    } else if (event.code == sf::Keyboard::Enter) {
        GameEvent event;
        event.type = GameEvent::RaceOpen;
        Course0::getInstance()->postEvent(event);
    }
}

void RacePlayerSelectScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        GameEvent event;
        event.type = GameEvent::MenuOpen;
        Course0::getInstance()->postEvent(event);
        _finishing = false;
    }
}

sf::String RacePlayerSelectScene::generateName() {
    size_t nameCount = sizeof(NAMES) / sizeof(sf::String);
    std::uniform_int_distribution dist(0, (int)(nameCount / 2 - 1));

    sf::String name;
    name += NAMES[2 * dist(gen)];
    name += " ";
    name += NAMES[2 * dist(gen) + 1];

    return name;
}
