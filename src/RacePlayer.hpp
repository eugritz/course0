#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.hpp"

#include <iostream>

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
    RacePlayer() {
        init();
    }

    RacePlayer(PlayerType type) {
        init();
        create(type);
    }

    void init() {
        _animationFrame = 0;
        _animationTick = 0;
        _speed = 0.f;
        _direction = LEFT;
    }

    void create(PlayerType type) {
        if (type == BROWN)
            loadBrownTextures();
        else if (type == BLACK)
            loadBlackTextures();

        _tileSize = sf::Vector2u(23, 16);
        _sprite.setTexture(**_sideTexture);
        _sprite.setTextureRect(sf::IntRect(0, 0, _tileSize.x, _tileSize.y));
        _sprite.setOrigin(_sprite.getLocalBounds().getSize() / 2.f);
        _direction = LEFT;
    }

    void update(const sf::Time &elapsed) {
        _animationTick += elapsed.asMicroseconds();
        while (_animationTick > RACE_PLAYER_ANIMATION_TICK) {
            _animationTick -= RACE_PLAYER_ANIMATION_TICK;

            _animationFrame++;
            if (_animationFrame > 1)
                _animationFrame = 0;

            sf::IntRect rect = _sprite.getTextureRect();
            rect.left = _animationFrame * _tileSize.x;
            _sprite.setTextureRect(rect);
        }
    }

    void setDirection(PlayerDirection direction) {
        if (_direction == direction)
            return;
        switch (direction) {
            case LEFT:
                if (_direction != RIGHT) {
                    _sprite.setTexture(**_sideTexture);
                    _tileSize = sf::Vector2u(23, 16);
                }
                _sprite.setTextureRect(sf::IntRect(0, 0, _tileSize.x, _tileSize.y));
                break;
            case UP:
                if (_direction != DOWN) {
                    _sprite.setTexture(**_baseTexture);
                    _tileSize = sf::Vector2u(16, 16);
                }
                _sprite.setTextureRect(sf::IntRect(0, _tileSize.y, _tileSize.x, _tileSize.y));
                break;
            case RIGHT:
                if (_direction != LEFT) {
                    _sprite.setTexture(**_sideTexture);
                    _tileSize = sf::Vector2u(23, 16);
                }
                _sprite.setTextureRect(
                        sf::IntRect(0, _tileSize.y, _tileSize.x, _tileSize.y));
                break;
            case DOWN:
                if (_direction != UP) {
                    _sprite.setTexture(**_baseTexture);
                    _tileSize = sf::Vector2u(16, 16);
                }
                _sprite.setTextureRect(sf::IntRect(0, 0, _tileSize.x, _tileSize.y));
                break;
        }
        _direction = direction;
    }

    float getSpeed() const {
        return _speed;
    }

    void setSpeed(float speed) {
        _speed = speed;
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_sprite, states);
    }

    void loadBrownTextures() {
        _baseTexture = GlobalResourceManager::refOr<sf::Texture>(
            "RACE_PLAYER_SPRITE_BROWN_HORSE_BASE",
            []() {
                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile("./Resources/Actor/Animals/Horse/SpriteSheetBrown.png")) {
                    std::cerr << "ERROR: Couldn't load \"SpriteSheetBrown.png\"\n";
                }
                return texture;
            }
        );

        _sideTexture = GlobalResourceManager::refOr<sf::Texture>(
            "RACE_PLAYER_SPRITE_BROWN_HORSE_SIDE",
            []() {
                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile("./Resources/Actor/Animals/Horse/SpriteSheetBrownSide.png")) {
                    std::cerr << "ERROR: Couldn't load \"SpriteSheetBrownSide.png\"\n";
                }
                return texture;
            }
        );
    }

    void loadBlackTextures() {
        _baseTexture = GlobalResourceManager::refOr<sf::Texture>(
            "RACE_PLAYER_SPRITE_BLACK_HORSE_BASE",
            []() {
                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile("./Resources/Actor/Animals/Horse/SpriteSheetBlack.png")) {
                    std::cerr << "ERROR: Couldn't load \"SpriteSheetBlack.png\"\n";
                }
                return texture;
            }
        );

        _sideTexture = GlobalResourceManager::refOr<sf::Texture>(
            "RACE_PLAYER_SPRITE_BLACK_HORSE_SIDE",
            []() {
                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile("./Resources/Actor/Animals/Horse/SpriteSheetBlackSide.png")) {
                    std::cerr << "ERROR: Couldn't load \"SpriteSheetBlackSide.png\"\n";
                }
                return texture;
            }
        );
    }
};
