#include "project0.h"

#include <SFML/Graphics.hpp>

#include <cmath>

#include "mandelbrot.h"
#include "zoomarea.h"

Project0 *Project0::_instance;

mandelbrot::Mandelbrot _mandel;
sf::RectangleShape _zoomFrame;

int _fillTime;
int _frameBlinkTime;
bool _frameShow;

Project0 *Project0::getInstance() {
    if (_instance == nullptr)
        _instance = new Project0();
    return _instance;
}

void Project0::start() {
    if (_window.isOpen()) return;

    sf::Vector2<Real> p1(-0.5, 0);
    Real rad1 = 1.5;
    sf::Vector2<Real> p2(-1.36022, 0.0653316);
    Real rad2 = 0.25;

    sf::Vector2i windowSize(WIDTH, HEIGHT);
    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "Project0");
    _mandel.create(windowSize, p1, rad1);

    ZoomArea zoom = calculateZoomArea(_mandel, p2, rad2);
    _zoomFrame.setSize(zoom.size);
    _zoomFrame.setOrigin(_zoomFrame.getSize() / 2.0f);
    _zoomFrame.setPosition(zoom.position);
    _zoomFrame.setFillColor(sf::Color::Transparent);
    _zoomFrame.setOutlineColor(sf::Color::Red);
    _zoomFrame.setOutlineThickness(2.0f);

    gameLoop();
}

void Project0::gameLoop() {
    while (_window.isOpen()) {
        sf::Time timeElapsed = _clock.restart();

        _window.clear();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        if (!_mandel.isRendered()) {
            _mandel.stepRender();
        } else if (!_mandel.isFilled()) {
            if (_fillTime > FILL_TIMEOUT) {
                _mandel.stepFill();
                _fillTime = 0;
            } else {
                _fillTime += timeElapsed.asMicroseconds();
            }
        }

        _window.draw(_mandel);

        if (_mandel.isFilled()) {
            if (_frameShow)
                _window.draw(_zoomFrame);

            if (_frameBlinkTime >= FRAME_BLINK_TIMEOUT) {
                _frameShow = !_frameShow;
                _frameBlinkTime = 0;
            }

            _frameBlinkTime += timeElapsed.asMicroseconds();
        }

        _window.display();
    }
}
