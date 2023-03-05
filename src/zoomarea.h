#pragma once

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"

struct ZoomArea {
    sf::Vector2f size;
    sf::Vector2f position;
};

ZoomArea calculateZoomArea(const mandelbrot::Mandelbrot &mandel, 
                           sf::Vector2<Real> origin, Real radius);
