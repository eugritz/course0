#include "Course0.h"

#include <SFML/Graphics.hpp>

#include "AuthorMenu.h"
#include "IntroScene.h"
#include "MainMenu.h"

Course0 *Course0::_instance;

Course0 *Course0::getInstance() {
    if (_instance == nullptr)
        _instance = new Course0();
    return _instance;
}

void Course0::start() {
    if (_window.isOpen()) return;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _window.create(sf::VideoMode(WIDTH, HEIGHT), "Course0",
            sf::Style::Default, settings);
    _scene = new IntroScene(&_window);
    gameLoop();
}

void Course0::gameLoop() {
    while (_window.isOpen()) {
        sf::Time timeElapsed = _clock.restart();

        _window.clear();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (_scene != nullptr && !_scene->handleEvent(event))
                continue;
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        while (!_eventBus.empty()) {
            GameEvent gameEvent = _eventBus.front();
            handleGameEvent(gameEvent);
            _eventBus.pop();
        }

        if (_scene != nullptr) {
            _scene->update(timeElapsed);
            _scene->draw(sf::RenderStates::Default);
        }

        _window.display();
    }
}

void Course0::handleGameEvent(GameEvent event) {
    switch (event) {
        case INTRO_OPEN:
            delete _scene;
            _scene = new IntroScene(&_window);
            _window.setFramerateLimit(0);
            break;
        case MENU_OPEN:
            delete _scene;
            _scene = new MainMenu(&_window);
            _window.setFramerateLimit(60);
            break;
        case AUTHOR_OPEN:
            delete _scene;
            _scene = new AuthorMenu(&_window);
            break;
        case EXIT:
            _window.close();
            break;
    };
}

void Course0::postEvent(GameEvent event) {
    _eventBus.push(event);
}
