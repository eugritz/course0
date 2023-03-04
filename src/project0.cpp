#include "project0.h"

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"

Project0 *Project0::_instance;
mandelbrot::Mandelbrot _mandel;

Project0 *Project0::getInstance() {
    if (_instance == nullptr)
        _instance = new Project0();
    return _instance;
}

void Project0::start() {
    if (_window.isOpen()) return;

    sf::Vector2i windowSize((mandelbrot::END.x - mandelbrot::BEGIN.x) / SCALE,
                            (mandelbrot::END.y - mandelbrot::BEGIN.y) / SCALE);
    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "Project0");

    _mandel.create(windowSize);
    _mandel.update();

    gameLoop();
}

void Project0::gameLoop() {
    while (_window.isOpen()) {
        int timeElapsed = _clock.restart().asMilliseconds();

        _window.clear();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _window.draw(_mandel);
        _window.display();
    }
}
