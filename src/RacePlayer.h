#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.hpp"

#define RACE_PLAYER_ANIMATION_TICK 100000

enum PlayerDirection {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

enum PlayerType {
    BROWN,
    BLACK
};

struct PlayerOption {
    sf::String name;
    PlayerType type;
};

class RacePlayer : public sf::Drawable, public sf::Transformable {
    sf::Sprite _sprite;
    SharedResource<sf::Texture> _baseTexture, _sideTexture;
    sf::Vector2u _tileSize;

    int _animationTick;
    int _animationFrame;

    PlayerDirection _direction;
    float _speed;

public:
    RacePlayer();
    RacePlayer(PlayerType type);

    void init();
    void create(PlayerType type);
    void update(const sf::Time &elapsed);

    void setDirection(PlayerDirection direction);
    sf::Vector2f getSize() const;

    float getSpeed() const;
    void setSpeed(float speed);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void loadBrownTextures();
    void loadBlackTextures();
};
