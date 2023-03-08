#pragma once

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"
#include "project0.h"
#include "scene.h"

#define INTRO_FILL_TIMEOUT 100
#define INTRO_FRAME_BLINK_COUNT 8
#define INTRO_FRAME_BLINK_TIMEOUT 450000

class IntroScene : public Scene {
    sf::Vector2i _size;

    int _zoomPoint;
    mandelbrot::Mandelbrot _mandel;
    sf::RectangleShape _zoomFrame;
    
    int _fillTime;
    int _frameBlinkTime;
    int _frameBlinkCount;
    bool _frameShow;
    bool _finishing;

public:
    IntroScene(sf::Vector2i size);

    void update(sf::Time elapsed);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool handleEvent(const sf::Event &event);

private:
    void setupZoomFrame();
};
