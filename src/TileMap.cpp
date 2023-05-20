#include "TileMap.h"

bool TileMap::load(const std::string &tileset, const sf::Vector2u &tileSize,
                   const int *tiles, unsigned int width, unsigned int height) {
    _tileSize = tileSize;
    _width = width;
    _height = height;
    if (!_tileset.loadFromFile(tileset))
        return false;

    createVertices(tileSize, tiles, width, height);
    return true;
}

bool TileMap::loadFromTexture(const sf::Texture &texture,
                              const sf::Vector2u &tileSize,
                              const int *tiles, unsigned int width,
                              unsigned int height) {
    _tileSize = tileSize;
    _width = width;
    _height = height;
    _tileset = texture;

    createVertices(tileSize, tiles, width, height);
    return true;
}

void TileMap::createVertices(const sf::Vector2u &tileSize, const int *tiles,
                             unsigned int width, unsigned int height) {
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            int tileNumber = tiles[i + j * width];
            if (tileNumber < 0)
                continue;

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
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}

sf::Vector2f TileMap::getSize() const {
    return sf::Vector2f(_width * _tileSize.x, _height * _tileSize.y);
}
