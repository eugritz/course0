#pragma once

#include <map>
#include <memory>
#include <vector>

#include "BlackPianoKey.h"
#include "Resources.hpp"
#include "WhitePianoKey.h"

class SynthesizerKeyboard : public sf::Drawable, public sf::Transformable {
    std::vector<std::shared_ptr<PianoKey>> _whiteKeys, _blackKeys;
    std::map<size_t, std::shared_ptr<PianoKey>> _mappings;
    size_t _last;

    SharedResource<sf::Font> _keyFont;

public:
    SynthesizerKeyboard();

    sf::Vector2f getSize() const;

    const std::shared_ptr<PianoKey> operator[](size_t index) const;
    std::shared_ptr<PianoKey> operator[](size_t index);

private:
    void setupKeys();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    std::shared_ptr<PianoKey> addWhiteKey(const sf::String &note);
    std::shared_ptr<PianoKey> addWhiteKey(const sf::String &note,
                                          std::shared_ptr<PianoKey> previous);
    std::shared_ptr<PianoKey> addBlackKey(const sf::String &note,
                                          std::shared_ptr<PianoKey> previous);
};
