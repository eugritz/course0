#pragma once

#include <SFML/Graphics.hpp>

class FragmentRectangleShape : public sf::Shape {
    sf::Vector2f _size;
    int _fx, _fy;

public:
    FragmentRectangleShape(sf::Vector2f size = {0, 0}, int fragX = 1,
                           int fragY = 1);

    const sf::Vector2f &getSize() const;
    void setSize(const sf::Vector2f &size);
    void setFragments(int fragX, int fragY);

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;
};
