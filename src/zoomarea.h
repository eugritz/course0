#pragma once

#include <SFML/Graphics.hpp>

#include "mandelbrot.h"

struct ZoomArea {
    sf::Vector2f size;
    sf::Vector2f position;
};

struct ZoomPoint {
    sf::Vector2<Real> position;
    Real radius;
};

const ZoomPoint ZOOM_POINTS[] = {
    { { -0.5, 0.0 }, 1.5 },
    { { -1.36022, 0.0653316 }, 0.25 },
};

const size_t POINTS_COUNT = sizeof(ZOOM_POINTS) / sizeof(ZoomPoint);

ZoomArea calculateZoomArea(const mandelbrot::Mandelbrot &mandel, 
                           sf::Vector2<Real> origin, Real radius);
