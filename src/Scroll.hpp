#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "RacePlayer.hpp"
#include "Resources.hpp"

class Scroll : public sf::Drawable, public sf::Transformable {
    float indent = 3.f;

    sf::Sprite _scroll;
    SharedResource<sf::Texture> _scrollTexture;

    RacePlayer _player;
    SharedResource<sf::Font> _font;
    sf::Text _name;

public:
    Scroll() { }
    Scroll(const sf::String &name, PlayerType type) {
        create(name, type);
    }

    void create(const sf::String &name, PlayerType type) {
        _scrollTexture = GlobalResourceManager::refOr<sf::Texture>(
            "SCROLL_TEXTURE",
            []() {
                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile("./Resources/scroll.png")) {
                    std::cerr << "ERROR: Couldn't load \"scroll.png\"\n";
                }
                return texture;
            }
        );
        _scroll.setTexture(**_scrollTexture);
        sf::Vector2u scrollSize = _scrollTexture->getSize();

        _font = GlobalResourceManager::ref<sf::Font>("SCROLL_FONT");
        _name.setFont(**_font);
        _name.setString(name);
        _name.setCharacterSize(8);

        float textCenterX = _name.getLocalBounds().getSize().x / 2.f;
        _name.setOrigin(-(scrollSize.x / 2.f - textCenterX),
                        -(scrollSize.y / 2.f + indent));
        _name.setFillColor(sf::Color::Black);

        _player.create(type);
        _player.setOrigin(-(float)(scrollSize.x / 2.f),
                          -(float)(scrollSize.y / 2.f - indent));
    }

    void setName(const sf::String &name) {
        _name.setString(name);
    };

    void scale(float factorX, float factorY) {
        sf::Transformable::scale(factorX, factorY);
        _name.setCharacterSize(_name.getCharacterSize() * factorY);
        indent *= factorY;

        float textCenterX = _name.getLocalBounds().getSize().x / 2.f;
        sf::Vector2f scrollSize = _scroll.getLocalBounds().getSize();
        _name.setOrigin(-(scrollSize.x * factorX / 2.f - textCenterX),
                        -(scrollSize.y * factorY / 2.f + indent));

        _player.setOrigin(-(float)(scrollSize.x / 2.f),
                          -(float)(scrollSize.y / 2.f - indent));
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_scroll, states);
        target.draw(_player, states);
        states.transform.scale(1 / getScale().x, 1 / getScale().y);
        target.draw(_name, states);
    }
};
