#include "RectangleShape2.h"

#include <cmath>
#include <iostream>

RectangleShape2::RectangleShape2() {
    _iters = 0;
    _itersX = 0;
    _itersY = 0;
    _fractured = false;
    _roundness = 0.f;
    _length = 0.f;
    _offset = 0.f;
    _step = 0.f;
    update();
}

RectangleShape2::RectangleShape2(const sf::Vector2f &size, std::size_t iters,
                                 float roundness, bool fractured) {
    init(size, iters, roundness, fractured);
    update();
}

void RectangleShape2::init(const sf::Vector2f &size, std::size_t iters,
                           float roundness, bool fractured) {
    _size = size;
    _iters = iters;
    _fractured = fractured;
    _roundness = roundness;
    _step = 1.f / (float)iters;

    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * roundness;
    calculateIters();
}

const sf::Vector2f &RectangleShape2::getSize() const {
    return _size;
}

void RectangleShape2::setSize(const sf::Vector2f &size) {
    _size = size;
    float smallSide = size.x > size.y ? size.y : size.x;
    _offset = smallSide * _roundness;
    calculateIters();
    update();
}

std::size_t RectangleShape2::getIterationCount() const {
    return _iters;
}

void RectangleShape2::setIterationCount(std::size_t iters, bool fractured) {
    _iters = iters;
    _step = 1.f / (float)iters;
    _fractured = fractured;
    calculateIters();
    update();
}

void RectangleShape2::setRoundness(float roundness) {
    _roundness = roundness;
    float smallSide = _size.x > _size.y ? _size.y : _size.x;
    _offset = smallSide * roundness;
    update();
}

std::size_t RectangleShape2::getPointCount() const {
    std::size_t points = 4 * _iters + 2 * _itersX + 2 * _itersY;
    if (points == 0)
        return 0;
    if (_fractured)
        points -= 1;
    return points;
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
        std::size_t nth = index - 2 * _itersX - _itersY - 3 * _iters;
        return sf::Vector2f(0, _offset + (_itersY - nth) * vert);
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

float RectangleShape2::getCurveLength() const {
    return _length;
}

void RectangleShape2::calculateIters() {
    if (!_fractured) {
        _itersX = _itersY = 1;
        return;
    }

    sf::Vector2f p0, p1(_offset, 0), p2(_offset, _offset);
    _length = bezier2Length(_iters, p0, p1, p2);

    _itersX = _iters * (_size.x - 2.f * _offset) / _length;
    _itersY = _iters * (_size.y - 2.f * _offset) / _length;
}

sf::Vector2f RectangleShape2::bezier2(const sf::Vector2f &p0,
                                      const sf::Vector2f &p1,
                                      const sf::Vector2f &p2, float t) {
    return (1 - t) * (1 - t) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
}

float RectangleShape2::bezier2Length(std::size_t iters, const sf::Vector2f &p0,
                                     const sf::Vector2f &p1,
                                     const sf::Vector2f &p2) {
    float length = 0;
    sf::Vector2f prev;
    for (size_t i = 0; i < iters; i++) {
        float t = (float)(i + 1) / (float)iters;
        sf::Vector2f next = RectangleShape2::bezier2(p0, p1, p2, t);
        float dist = std::sqrt(std::pow((next.x - prev.x), 2) +
                               std::pow((next.y - prev.y), 2));

        length += dist;
        prev = next;
    }
    return length;
}
