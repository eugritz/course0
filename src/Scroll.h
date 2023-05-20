#pragma once

#include <SFML/Graphics.hpp>

#include "RacePlayer.h"
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
    Scroll();
    Scroll(const PlayerOption *option);
    void create(const PlayerOption *option);

    sf::Vector2f getSize() const;
    void setOutlineColor(const sf::Color &color);
    void scale(float factorX, float factorY);

    const PlayerOption *getOption() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
