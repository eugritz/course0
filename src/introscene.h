#pragma once

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"
#include "project0.h"
#include "scene.h"

#define INTRO_FILL_TIMEOUT 100
#define INTRO_FRAME_BLINK_COUNT 8
#define INTRO_FRAME_BLINK_TIMEOUT 450000

class IntroScene : public Scene {
    int _zoomPoint;
    mandelbrot::Mandelbrot _mandel;
    sf::RectangleShape _zoomFrame;
    
    int _fillTime;
    int _frameBlinkTime;
    int _frameBlinkCount;
    bool _frameShow;
    bool _finishing;

public:
    IntroScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setupZoomFrame();
};
