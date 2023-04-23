#include "project0.h"

#include <SFML/Graphics.hpp>

#include "authormenu.h"
#include "graphscene.h"
#include "integralmenu.h"
#include "introscene.h"
#include "mainmenu.h"
#include "solutionmenu.h"
#include "tablemenu.h"

Project0 *Project0::_instance;

Project0 *Project0::getInstance() {
    if (_instance == nullptr)
        _instance = new Project0();
    return _instance;
}

void Project0::start() {
    if (_window.isOpen()) return;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _window.create(sf::VideoMode(WIDTH, HEIGHT), "Project0",
            sf::Style::Default, settings);
    _scene = new IntroScene(&_window);
    gameLoop();
}

void Project0::gameLoop() {
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

void Project0::handleGameEvent(GameEvent event) {
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
        case GRAPHS_OPEN:
            delete _scene;
            _scene = new GraphScene(&_window);
            break;
        case TABLE_OPEN:
            delete _scene;
            _scene = new TableMenu(&_window);
            break;
        case SOLUTION_OPEN:
            delete _scene;
            _scene = new SolutionMenu(&_window);
            break;
        case INTEGRAL_OPEN:
            delete _scene;
            _scene = new IntegralMenu(&_window);
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

void Project0::postEvent(GameEvent event) {
    _eventBus.push(event);
}
