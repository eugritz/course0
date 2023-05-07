#include "RectangleShape2.h"

RectangleShape2::RectangleShape2() {
    _iters = 0;
    _itersX = 0;
    _itersY = 0;
    _roundness = 0.f;
    _step = 0.f;
    _offset = 0.f;
    update();
}

RectangleShape2::RectangleShape2(const sf::Vector2f &size, std::size_t iters,
                                 float roundness) {
    init(size, iters, roundness);
    calculateIters(_iters, _iters);
    update();
}

RectangleShape2::RectangleShape2(const sf::Vector2f &size, std::size_t iters,
                                 std::size_t itersX, std::size_t itersY,
                                 float roundness) {
    sf::RectangleShape a;
    init(size, iters, roundness);
    calculateIters(itersX, itersY);
    update();
}

void RectangleShape2::init(const sf::Vector2f &size, std::size_t iters,
                           float roundness) {
    _size = size;
    _iters = iters + 1;
    _roundness = roundness;
    _step = 1.f / (float)iters;

    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * roundness;
}

const sf::Vector2f &RectangleShape2::getSize() const {
    return _size;
}

void RectangleShape2::setSize(const sf::Vector2f &size) {
    _size = size;
    float smallSide = size.x > size.y ? size.y : size.x;
    _offset = smallSide * _roundness;

    _itersX = _iters * (1.f - 2.f * _offset / _size.x);
    _itersY = _iters * (1.f - 2.f * _offset / _size.y);

    update();
}

void RectangleShape2::setIterationCount(std::size_t iters) {
    _iters = iters + 1;
    _step = 1.f / (float)iters;

    _itersX = _iters * (1.f - 2.f * _offset / _size.x);
    _itersY = _iters * (1.f - 2.f * _offset / _size.y);

    update();
}

void RectangleShape2::setIterationCount(std::size_t iters, std::size_t itersX,
                       std::size_t itersY) {
    _iters = iters + 1;
    _step = 1.f / (float)iters;

    _itersX = itersX * (1.f - 2.f * _offset / _size.x);
    _itersY = itersY * (1.f - 2.f * _offset / _size.y);

    update();
}

void RectangleShape2::setRoundness(float roundness) {
    _roundness = roundness;
    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * roundness;
    update();
}

std::size_t RectangleShape2::getPointCount() const {
    return 4 * _iters + 2 * _itersX + 2 * _itersY;
}

sf::Vector2f RectangleShape2::getPoint(std::size_t index) const {
    float horiz = (_size.x - 2.f * _offset) / _itersX;
    float vert = (_size.y - 2.f * _offset) / _itersY;

    if (index < _itersX - 1) {
        // Top
        std::size_t nth = index + 1;
        return sf::Vector2f(_offset + horiz * nth, 0);
    } else if (index < _itersX + _iters) {
        // Top-right corner
        std::size_t nth = index - _itersX + 1;
        sf::Vector2f p0(_size.x - _offset, 0);
        sf::Vector2f p1(_size.x, 0);
        sf::Vector2f p2(_size.x, _offset);
        float t = nth * _step;
        return bezier2(p0, p1, p2, t);
    } else if (index < _itersX + _itersY + _iters - 1) {
        // Right
        std::size_t nth = index - _itersX - _iters + 1;
        return sf::Vector2f(_size.x, _offset + vert * nth);
    } else if (index < _itersX + _itersY + 2 * _iters) {
        // Bottom-right corner
        std::size_t nth = index - _itersX - _itersY - _iters + 1;
        sf::Vector2f p0(_size.x, _size.y - _offset);
        sf::Vector2f p1(_size.x, _size.y);
        sf::Vector2f p2(_size.x - _offset, _size.y);
        float t = nth * _step;
        return bezier2(p0, p1, p2, t);
    } else if (index < 2 * _itersX + _itersY + 2 * _iters - 1) {
        // Bottom
        std::size_t nth = index - _itersX - _itersY - 2 * _iters + 1;
        return sf::Vector2f(_offset + (_itersX - nth) * horiz, _size.y);
    } else if (index < 2 * _itersX + _itersY + 3 * _iters) {
        // Bottom-left corner
        std::size_t nth = index - 2 * _itersX - _itersY - 2 * _iters + 1;
        sf::Vector2f p0(_offset, _size.y);
        sf::Vector2f p1(0, _size.y);
        sf::Vector2f p2(0, _size.y - _offset);
        float t = nth * _step;
        return bezier2(p0, p1, p2, t);
    } else if (index < 2 * _itersX + 2 * _itersY + 3 * _iters - 1) {
        // Left
        std::size_t nth = index - 2 * _itersX - _itersY - 3 * _itersX;
        return sf::Vector2f(0, _offset + (_iters - nth) * vert);
    } else {
        // Top-left corner
        std::size_t nth = index - 2 * _itersX - 2 * _itersY - 3 * _iters + 1;
        sf::Vector2f p0(0, _offset);
        sf::Vector2f p1(0, 0);
        sf::Vector2f p2(_offset, 0);
        float t = nth * _step;
        return bezier2(p0, p1, p2, t);
    }

    return sf::Vector2f();
}

void RectangleShape2::calculateIters(std::size_t x, std::size_t y) {
    if (_size.x - 2.f * _offset == 0.f) _itersX = 0;
    else _itersX = x * (1.f - 2.f * _offset / _size.x);
    if (_size.y - 2.f * _offset == 0.f) _itersY = 0;
    else _itersY = y * (1.f - 2.f * _offset / _size.y);
}

sf::Vector2f RectangleShape2::bezier2(const sf::Vector2f &p0,
                                      const sf::Vector2f &p1,
                                      const sf::Vector2f &p2, float t) {
    return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
}
