#include "project0.h"

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"

Project0 *Project0::_instance;
mandelbrot::Mandelbrot _mandel;
int _fillTime;

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
    gameLoop();
}

void Project0::gameLoop() {
    while (_window.isOpen()) {
        long long timeElapsed = _clock.restart().asMicroseconds();

        _window.clear();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        if (!_mandel.isRendered())
            _mandel.stepRender();
        else if (!_mandel.isFilled() && _fillTime > FILL_TIMEOUT) {
            _mandel.stepFill();
            _fillTime = 0;
        } else if (!_mandel.isFilled())
            _fillTime += timeElapsed;

        _window.draw(_mandel);
        _window.display();
    }
}
