#include "RacePlayerSelectScene.h"

#include "Course0.h"
#include "GameEvent.hpp"
#include "RacePlayer.hpp"
#include "RaceScene.h"
#include "Resources.hpp"
#include "Scroll.hpp"

RacePlayerSelectScene::RacePlayerSelectScene(sf::RenderTarget *target)
        : Scene(target) {
    _finishing = false;
}

void RacePlayerSelectScene::update(sf::Time elapsed) {
}

void RacePlayerSelectScene::draw(sf::RenderStates states) {
    Scroll scroll("yoooo. bruh", BROWN);
    scroll.scale(RACE_PIXEL_SCALE, RACE_PIXEL_SCALE);
    _target->draw(scroll);
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
