#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class MenuContainer : public sf::Drawable {
    sf::Vector2f _position;
    sf::Vector2f _origin;
    sf::Vector2f _size;
    bool _isSizeFixed;

    std::vector<sf::Text> _items;
    std::size_t _current;

    sf::Font _font;
    unsigned _characterSize;
    float _indent;

public:
    MenuContainer();
    MenuContainer(const sf::Font &font, unsigned characterSize = 30);
    MenuContainer(std::size_t size, const sf::Font &font,
                  unsigned characterSize = 30);

    void create(const sf::Font &font, unsigned characterSize = 30);
    void create(std::size_t size, const sf::Font &font,
                unsigned characterSize = 30);
    void reset();

    sf::Text &operator[](std::size_t index);
    const sf::Text &operator[](std::size_t index) const;

    std::size_t addItem(const sf::String &title);
    std::size_t fillItem(const sf::String &title);

    std::size_t getItemCount() const;
    sf::Vector2f getSize() const;

    void setPosition(const sf::Vector2f &position);
    void setOrigin(const sf::Vector2f &origin);
    void setIndent(float indent);

    const sf::Vector2f &setFixedSize(const sf::Vector2f &size);
    void resetSize();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
