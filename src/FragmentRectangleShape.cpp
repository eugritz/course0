#include "FragmentRectangleShape.h"

FragmentRectangleShape::FragmentRectangleShape(sf::Vector2f size, int fragX,
                                               int fragY) {
    _size = size;
    _fx = fragX;
    _fy = fragY;
    update();
}


const sf::Vector2f &FragmentRectangleShape::getSize() const {
    return _size;
}

void FragmentRectangleShape::setSize(const sf::Vector2f &size) {
    _size = size;
    update();
}

void FragmentRectangleShape::setFragments(int fragX, int fragY) {
    _fx = fragX;
    _fy = fragY;
    update();
}

std::size_t FragmentRectangleShape::getPointCount() const {
    return 4 + (_fx - 1) * 2 + (_fy - 1) * 2;
}

sf::Vector2f FragmentRectangleShape::getPoint(std::size_t index) const {
    std::size_t points = getPointCount();
    std::size_t top = points - (_fx + 1) - (_fy - 1) * 2;
    std::size_t right = points - (_fx + 1) - (_fy - 1);
    std::size_t bot = points - (_fy - 1);

    if (index < top) {
        std::size_t nth = index;
        return sf::Vector2f(nth * _size.x / _fx, 0);
    } else if (index < right) {
        std::size_t nth = index - top;
        return sf::Vector2f(_size.x, nth * _size.y / _fy);
    } else if (index < bot) {
        std::size_t nth = index - right;
        return sf::Vector2f(_size.x - nth * _size.x / _fx, _size.y);
    } else if (index >= bot) {
        std::size_t nth = index - bot;
        return sf::Vector2f(0, nth * _size.y / _fy);
    }

    return sf::Vector2f();
}
