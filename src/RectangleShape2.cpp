#include "RectangleShape2.h"

RectangleShape2::RectangleShape2() {
    _iters = 0;
    _rounding = 0.f;
    _step = 0.f;
    _offset = 0.f;
    update();
}

RectangleShape2::RectangleShape2(sf::Vector2f size, std::size_t iters,
                                 float rounding) {
    _size = size;
    _iters = iters + 1;
    _rounding = rounding;
    _step = 1.f / (float)iters;

    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * rounding;
    update();
}

const sf::Vector2f &RectangleShape2::getSize() const {
    return _size;
}

void RectangleShape2::setSize(const sf::Vector2f &size) {
    _size = size;
    float smallSide = size.x > size.y ? size.y : size.x;
    _offset = smallSide * _rounding;
    update();
}

void RectangleShape2::setIterationCount(std::size_t iters) {
    _iters = iters + 1;
    _step = 1.f / (float)iters;
    update();
}

void RectangleShape2::setRounding(float rounding) {
    _rounding = rounding;
    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * rounding;
    update();
}

std::size_t RectangleShape2::getPointCount() const {
    return 4 * _iters;
}

sf::Vector2f RectangleShape2::getPoint(std::size_t index) const {
    if (index < _iters) {
        // Top-right corner
        sf::Vector2f p0(_size.x - _offset, 0);
        sf::Vector2f p1(_size.x, 0);
        sf::Vector2f p2(_size.x, _offset);
        float t = index * _step;
        return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
    } else if (index < 2 * _iters) {
        // Bottom-right corner
        std::size_t nth = index - _iters;
        sf::Vector2f p0(_size.x, _size.y - _offset);
        sf::Vector2f p1(_size.x, _size.y);
        sf::Vector2f p2(_size.x - _offset, _size.y);
        float t = nth * _step;
        return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
    } else if (index < 3 * _iters) {
        // Bottom-left corner
        std::size_t nth = index - 2 * _iters;
        sf::Vector2f p0(_offset, _size.y);
        sf::Vector2f p1(0, _size.y);
        sf::Vector2f p2(0, _size.y - _offset);
        float t = nth * _step;
        return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
    } else {
        // Top-left corner
        std::size_t nth = index - 3 * _iters;
        sf::Vector2f p0(0, _offset);
        sf::Vector2f p1(0, 0);
        sf::Vector2f p2(_offset, 0);
        float t = nth * _step;
        return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
    }

    return sf::Vector2f();
}
