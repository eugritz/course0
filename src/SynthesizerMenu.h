#pragma once

#include <SFML/Graphics.hpp>

#include "MenuScene.h"

#define SYNTHESIZER_MENU_ITEM_COUNT 15
#define SYNTHESIZER_MENU_ITEM_LENGTH 44

class SynthesizerMenu : public MenuScene {
    bool _finishing;

public:
    SynthesizerMenu(sf::RenderTarget *target);
    ~SynthesizerMenu();
    void setupMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
