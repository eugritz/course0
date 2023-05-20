#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
    unsigned int _width, _height;

public:
    bool load(const std::string &tileset, const sf::Vector2u &tileSize,
              const int *tiles, unsigned int width, unsigned int height);
    bool loadFromTexture(const sf::Texture &texture,
                         const sf::Vector2u &tileSize,
                         const int *tiles, unsigned int width,
                         unsigned int height);

    sf::Vector2f getSize() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void createVertices(const sf::Vector2u &tileSize, const int *tiles,
                        unsigned int width, unsigned int height);
};
