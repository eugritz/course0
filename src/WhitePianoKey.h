#pragma once

#include <SFML/Graphics.hpp>

#include "PianoKey.h"

class WhitePianoKey : public PianoKey {
    sf::String _note;
    sf::Font _font;

public:
    WhitePianoKey(const sf::Font &font, const sf::String &note);

    sf::Vector2f getSize() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
