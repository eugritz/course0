#include "mandelbrot.h"
#include "complex.hpp"

using namespace mandelbrot;

void stepColor(sf::Color &clr);

Mandelbrot::Mandelbrot() {}
Mandelbrot::Mandelbrot(sf::Vector2i size, sf::Vector2<Real> begin,
                       sf::Vector2<Real> end)
        : _size(size), _begin(begin), _end(end) {
    _image.create(_size.x, _size.y);
}

void Mandelbrot::create(sf::Vector2i size, sf::Vector2<Real> begin,
                        sf::Vector2<Real> end) {
    _size = size;
    _begin = begin;
    _end = end;
    _image.create(_size.x, _size.y);
}

void Mandelbrot::update() {
    const Real epsilon = 0.005;
    const int iters = 250;
    const int ballout = 10000;

    sf::Color color;
    int imageX = 0, imageY = 0;
    for (Real currX = _begin.x; currX <= _end.x; currX += epsilon, imageX++) {
        imageY = 0;
        while (imageX >= _size.x)
            imageX--;
        for (Real currY = _begin.y; currY <= _end.y; currY += epsilon, imageY++) {
            while (imageY >= _size.y)
                imageY--;
            color = sf::Color::Black;

            Complex<Real> curr;
            _image.setPixel(imageX, imageY, sf::Color::Black);
            for (int i = 0; i < iters; i++) {
                if (curr.module_sqr() >= ballout) {
                    _image.setPixel(imageX, imageY, color);
                    break;
                }

                curr = curr*curr + Complex<Real>(currX, currY);
                stepColor(color);
            }
        }
    }
}

void Mandelbrot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromImage(_image);
    sprite.setTexture(texture);
    target.draw(sprite, states);
}

void stepColor(sf::Color &clr) {
	clr.r = clr.r + 5 < 0x100 ? clr.r + 5 : 0xff;
	clr.g = clr.g + 3 < 0x100 ? clr.g + 5 : 0xff;
	clr.b = clr.b + 2 < 0x100 ? clr.b + 5 : 0xff;
}
