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

    sf::Shader _outline;
    sf::Color _outlineColor;

    const PlayerOption *_option;

public:
    Scroll() { }
    Scroll(const PlayerOption *option) {
        _option = option;
        create(option);
    }

    void create(const PlayerOption *option) {
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
        _name.setString(option->name);
        _name.setCharacterSize(8);

        float textCenterX = _name.getLocalBounds().getSize().x / 2.f;
        _name.setOrigin(-(scrollSize.x / 2.f - textCenterX),
                        -(scrollSize.y / 2.f + indent));
        _name.setFillColor(sf::Color::Black);

        _player.create(option->type);
        _player.setOrigin(-(float)(scrollSize.x / 2.f),
                          -(float)(scrollSize.y / 2.f - indent));

        const std::string fragmentSource = BINARY_RESOURCE(outline_frag);
        _outline.loadFromMemory(fragmentSource, sf::Shader::Fragment);
        _outline.setUniform("textureOffset",
                            1.0f / _scrollTexture->getSize().x);
        _outline.setUniform("texture", sf::Shader::CurrentTexture);
        setOutlineColor(sf::Color::Transparent);
    }

    sf::Vector2f getSize() const {
        sf::Vector2f size = _scroll.getLocalBounds().getSize();
        sf::Vector2f scale = getScale();
        return sf::Vector2f(size.x * scale.x, size.y * scale.y);
    }

    void setOutlineColor(const sf::Color &color) {
        _outlineColor = color;
        _outline.setUniform("color", sf::Glsl::Vec4(_outlineColor.r / 255.f,
                                                    _outlineColor.g / 255.f,
                                                    _outlineColor.b / 255.f,
                                                    _outlineColor.a / 255.f));
    }

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

    const PlayerOption *getOption() const {
        return _option;
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        states.shader = &_outline;
        target.draw(_scroll, states);
        states.shader = nullptr;

        target.draw(_player, states);

        states.transform.scale(1 / getScale().x, 1 / getScale().y);
        target.draw(_name, states);
    }
};
