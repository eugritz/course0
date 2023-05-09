#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
    unsigned int _width, _height;

public:
    bool load(const std::string &tileset, sf::Vector2u tileSize,
              const int *tiles, unsigned int width, unsigned int height) {
        _tileSize = tileSize;
        _width = width;
        _height = height;
        if (!_tileset.loadFromFile(tileset))
            return false;

        _vertices.setPrimitiveType(sf::Quads);
        _vertices.resize(width * height * 4);

        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                int tileNumber = tiles[i + j * width];

                int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

                sf::Vertex *quad = &_vertices[(i + j * width) * 4];
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(_width * _tileSize.x, _height * _tileSize.y);
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &_tileset;
        target.draw(_vertices, states);
    }
};