#pragma once

#include <SFML/Graphics.hpp>

#include "menuscene.h"

#define TABLE_MENU_ITEM_COUNT 19
#define TABLE_MENU_ITEM_LENGTH 45

class TableMenu : public MenuScene {
    bool _finishing;

public:
    TableMenu(sf::RenderTarget *target);
    void setupMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
