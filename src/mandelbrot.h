#pragma once

#include <SFML/Graphics.hpp>

#include <queue>

#include "complex.hpp"

namespace mandelbrot {

const int QUEUED = 1;
const int LOADED = 2;

const sf::Vector2<Real> BEGIN(-2, -1.25);
const sf::Vector2<Real> END(1, 1.25);

class Mandelbrot : public sf::Drawable {
    sf::Vector2<Real> _start;
    sf::Vector2<Real> _begin, _end;

    sf::Image _image;
    sf::Vector2i _size;

    std::queue<unsigned> _queue;
    unsigned *_done, *_data;

public:
    Mandelbrot();
    Mandelbrot(sf::Vector2i size, sf::Vector2<Real> begin = BEGIN,
               sf::Vector2<Real> end = END);
    ~Mandelbrot();

    void create(sf::Vector2i size, sf::Vector2<Real> begin = BEGIN,
                sf::Vector2<Real> end = END);

    void setStartPosition(Real x, Real y);

    void stepRender();
    void render();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void push(unsigned nth);
    void scan(unsigned nth);
    int load(unsigned nth, unsigned x, unsigned y);

    int iterate(Real x, Real y);
    int iterate(unsigned nth, unsigned col, unsigned row);
};

}
