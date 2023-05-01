#include "Line.h"

Line::Line(float width) {
    _width = width;
    update();
}

Line::Line(const sf::Vector2f &start, const sf::Vector2f &end, float width) {
    setPoints(start, end);
}

void Line::setPoints(const sf::Vector2f &start, const sf::Vector2f &end) {
    _start = start;
    _end = end;
    update();
}

sf::Vector2f Line::getStart() const {
    return _start;
}

sf::Vector2f Line::getEnd() const {
    return _end;
}

float Line::getLength() const {
    float dx = _start.x - _end.x;
    float dy = _start.y - _end.y;
    return std::sqrt(dx*dx + dy*dy);
}

sf::Vector2f Line::getSize() const {
    return sf::Vector2f(getLength(), _width);
}

std::size_t Line::getPointCount() const {
    return 4;
}

sf::Vector2f Line::getPoint(std::size_t index) const {
    float rad = std::asin((_end.y - _start.y) / getLength());
    switch (index)
    {
        default:
        case 0: return _rotate(0, -_width, rad);
        case 1: return _rotate(getLength(), -_width, rad);
        case 2: return _rotate(getLength(), _width, rad);
        case 3: return _rotate(0, _width, rad);
    }
}

sf::VertexArray Line::toArray() const {
    sf::VertexArray arr(sf::TriangleStrip, 4);
    arr[0] = getPoint(0);
    arr[1] = getPoint(3);
    arr[2] = getPoint(1);
    arr[3] = getPoint(2);

    arr[0].color = getFillColor();
    arr[1].color = getFillColor();
    arr[2].color = getFillColor();
    arr[3].color = getFillColor();
    return arr;
}

sf::Vector2f Line::_rotate(float X, float Y, float rad) const {
    float x = X * std::cos(rad) - Y * std::sin(rad);
    float y = X * std::sin(rad) + Y * std::cos(rad);
    return sf::Vector2f(_start.x + x, _start.y + y);
}
