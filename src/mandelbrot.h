#pragma once

#include <SFML/Graphics.hpp>
#include "complex.hpp"

namespace mandelbrot {

const sf::Vector2<Real> BEGIN(-2, -1.25);
const sf::Vector2<Real> END(1, 1.25);

class Mandelbrot : public sf::Drawable {
    sf::Vector2i _size;
    sf::Vector2<Real> _begin, _end;

    sf::Image _image;

public:
    Mandelbrot();
    Mandelbrot(sf::Vector2i size, sf::Vector2<Real> begin = BEGIN,
               sf::Vector2<Real> end = END);

    void create(sf::Vector2i size, sf::Vector2<Real> begin = BEGIN,
                sf::Vector2<Real> end = END);

    void setSize(int width, int height);

    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

}
