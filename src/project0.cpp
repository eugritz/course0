#include "project0.h"

#include <SFML/Graphics.hpp>

#include "introscene.h"
#include "mandelbrot.h"
#include "zoomarea.h"

Project0 *Project0::_instance;

Project0 *Project0::getInstance() {
    if (_instance == nullptr)
        _instance = new Project0();
    return _instance;
}

void Project0::start() {
    if (_window.isOpen()) return;
    _window.create(sf::VideoMode(WIDTH, HEIGHT), "Project0");
    _scene = new IntroScene({ WIDTH, HEIGHT });
    gameLoop();
}

void Project0::gameLoop() {
    while (_window.isOpen()) {
        sf::Time timeElapsed = _clock.restart();

        _window.clear();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (!_scene->handleEvent(event))
                continue;
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _scene->update(timeElapsed);
        _scene->draw(_window, sf::RenderStates::Default);

        _window.display();
    }
}
