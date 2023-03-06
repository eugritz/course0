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
    { { -0.5,     0.0       }, 1.5 },
    { { -1.36022, 0.0653316 }, 0.25 },
    { { -1.25,    0.085     }, 0.0417 },
    { { -1.24,    0.11      }, 0.00695 },
    { { -1.244,   0.108     }, 0.00115833 },
    { { -1.2435,  0.1077    }, 0.000193055 },
};

const size_t ZOOM_START = 0;
const size_t ZOOM_COUNT = sizeof(ZOOM_POINTS) / sizeof(ZoomPoint);

ZoomArea calculateZoomArea(const mandelbrot::Mandelbrot &mandel, 
                           sf::Vector2<Real> origin, Real radius);
