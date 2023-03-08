#include "introscene.h"

#include "mandelbrot.h"
#include "zoomarea.h"

IntroScene::IntroScene(sf::Vector2i size) {
    _zoomPoint = 0;
    _frameBlinkTime = 0;
    _frameBlinkCount = 0;
    _frameShow = false;

    _mandel.create(size, ZOOM_POINTS[_zoomPoint].position,
            ZOOM_POINTS[_zoomPoint].radius);
    _zoomPoint++;
    setupZoomFrame();
}

void IntroScene::update(sf::Time elapsed) {
    if (!_mandel.isRendered()) {
        _mandel.stepRender();
    } else if (!_mandel.isFilled()) {
        if (_fillTime > INTRO_FILL_TIMEOUT) {
            _mandel.stepFill();
            _fillTime = 0;
        } else {
            _fillTime += elapsed.asMicroseconds();
        }
    }

    bool frameComplete = _frameBlinkCount > INTRO_FRAME_BLINK_COUNT;
    bool lastPoint = _zoomPoint == ZOOM_COUNT;
    if (frameComplete || (_mandel.isFilled() && lastPoint)) {
        _frameBlinkCount = 0;
        _frameBlinkTime = 0;
        _frameShow = false;

        if (lastPoint)
            _zoomPoint = 0;
        sf::Vector2i windowSize(WIDTH, HEIGHT);
        _mandel.create(windowSize, ZOOM_POINTS[_zoomPoint].position,
                ZOOM_POINTS[_zoomPoint].radius);
        _zoomPoint++;
        setupZoomFrame();
    } else if (_mandel.isFilled()) {
        if (_frameBlinkTime >= INTRO_FRAME_BLINK_TIMEOUT) {
            _frameShow = !_frameShow;
            _frameBlinkTime = 0;
            _frameBlinkCount++;
        }

        _frameBlinkTime += elapsed.asMicroseconds();
    }
    
    if (_frameBlinkCount >= INTRO_FRAME_BLINK_COUNT)
        _frameShow = false;
}


void IntroScene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_mandel, states);
    if (_frameShow) {
        target.draw(_zoomFrame, states);
    }
}

bool IntroScene::handleEvent(const sf::Event &event) {
    return true;
}

void IntroScene::setupZoomFrame() {
    ZoomArea zoom = calculateZoomArea(_mandel, ZOOM_POINTS[_zoomPoint].position,
            ZOOM_POINTS[_zoomPoint].radius);

    _zoomFrame.setSize(zoom.size);
    _zoomFrame.setOrigin(_zoomFrame.getSize() / 2.0f);
    _zoomFrame.setPosition(zoom.position);
    _zoomFrame.setFillColor(sf::Color::Transparent);
    _zoomFrame.setOutlineColor(sf::Color::Red);
    _zoomFrame.setOutlineThickness(2.0f);
} 
