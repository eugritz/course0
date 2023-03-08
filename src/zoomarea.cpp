#include "zoomarea.h"

ZoomArea calculateZoomArea(const mandelbrot::Mandelbrot &mandel, 
                           sf::Vector2<Real> origin, Real radius) {
    sf::Vector2u size = mandel.getSize();
    sf::Vector2<Real> begin = mandel.getFirstPoint();
    sf::Vector2<Real> end = mandel.getSecondPoint();

    Real stepX = (end.x - begin.x) / size.x;
    Real stepY = (begin.y - end.y) / size.y;

    return {
        sf::Vector2f(radius * 2.0 / stepX, radius * 2.0 / stepY),
        sf::Vector2f((origin.x - begin.x) / stepX, (begin.y - origin.y) / stepY)
    };
}
