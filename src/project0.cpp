#include "project0.h"

#include <SFML/Graphics.hpp>

#include <cmath>

#include "mandelbrot.h"
#include "zoomarea.h"

Project0 *Project0::_instance;

int _zoomPoint = 0;
mandelbrot::Mandelbrot _mandel;
sf::RectangleShape _zoomFrame;

int _fillTime;
int _frameBlinkTime;
int _frameBlinkCount;
bool _frameShow;
bool _frameComplete;

Project0 *Project0::getInstance() {
    if (_instance == nullptr)
        _instance = new Project0();
    return _instance;
}

void Project0::start() {
    if (_window.isOpen()) return;

    sf::Vector2i windowSize(WIDTH, HEIGHT);
    _window.create(sf::VideoMode(windowSize.x, windowSize.y), "Project0");

    _mandel.create(windowSize, ZOOM_POINTS[_zoomPoint].position,
            ZOOM_POINTS[_zoomPoint].radius);
    _zoomPoint++;
    setupZoomFrame();

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

        bool lastPoint = _zoomPoint == POINTS_COUNT;
        if (_frameComplete || (_mandel.isFilled() && lastPoint)) {
            _frameComplete = false;
            _frameBlinkCount = 0;
            _frameBlinkTime = 0;

            if (lastPoint)
                _zoomPoint = 0;
            sf::Vector2i windowSize(WIDTH, HEIGHT);
            _mandel.create(windowSize, ZOOM_POINTS[_zoomPoint].position,
                    ZOOM_POINTS[_zoomPoint].radius);
            _zoomPoint++;
            setupZoomFrame();
        } else if (_mandel.isFilled()) {
            if (_frameShow) {
                _window.draw(_zoomFrame);
                _frameComplete = _frameBlinkCount > FRAME_BLINK_COUNT;
            }

            if (_frameBlinkTime >= FRAME_BLINK_TIMEOUT) {
                _frameShow = !_frameShow;
                _frameBlinkTime = 0;
                _frameBlinkCount++;
            }

            _frameBlinkTime += timeElapsed.asMicroseconds();
        }

        _window.display();
    }
}

void Project0::setupZoomFrame() {
    ZoomArea zoom = calculateZoomArea(_mandel, ZOOM_POINTS[_zoomPoint].position,
            ZOOM_POINTS[_zoomPoint].radius);

    _zoomFrame.setSize(zoom.size);
    _zoomFrame.setOrigin(_zoomFrame.getSize() / 2.0f);
    _zoomFrame.setPosition(zoom.position);
    _zoomFrame.setFillColor(sf::Color::Transparent);
    _zoomFrame.setOutlineColor(sf::Color::Red);
    _zoomFrame.setOutlineThickness(2.0f);
}
