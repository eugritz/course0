#pragma once

#include <SFML/Graphics.hpp>

#include <queue>

#include "complex.hpp"

namespace mandelbrot {

const int QUEUED = 1;
const int LOADED = 2;

const sf::Vector2<Real> BEGIN(-2, 1.25);
const sf::Vector2<Real> END(1, -1.25);

class Mandelbrot : public sf::Drawable {
    const int ITERS = 500;

    sf::Vector2<Real> _begin;
    sf::Vector2<Real> _end;
    Real _stepX, _stepY;

    sf::Vector2u _size;
    sf::Image _image;

    unsigned *_done, *_data;
    std::queue<unsigned> _queue;

    bool _rendered, _filled;
    unsigned _fillStep;

public:
    Mandelbrot();
    Mandelbrot(const sf::Vector2u &size, const sf::Vector2<Real> &origin,
               Real radius);
    Mandelbrot(const sf::Vector2u &size, const sf::Vector2<Real> &begin = BEGIN,
               const sf::Vector2<Real> &end = END);
    ~Mandelbrot();

    void init();
    void create(const sf::Vector2u &size, const sf::Vector2<Real> &origin,
                Real radius);
    void create(const sf::Vector2u &size, const sf::Vector2<Real> &begin = BEGIN,
                const sf::Vector2<Real> &end = END);
    void reset();

    sf::Vector2u getSize() const;
    sf::Vector2<Real> getFirstPoint() const;
    sf::Vector2<Real> getSecondPoint() const;

    bool isRendered() const;
    bool isFilled() const;

    void stepRender();
    void stepFill();
    void render();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    int load(unsigned nth, unsigned x, unsigned y);
    void push(unsigned nth);
    void scan(unsigned nth);

    int iterate(Real x, Real y);
    int iterate(unsigned nth, unsigned col, unsigned row);
};

}
