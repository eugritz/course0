#pragma once

#include <SFML/Graphics.hpp>

#include "menuscene.h"

#define TABLE_MENU_ITEM_COUNT 22
#define TABLE_MENU_ITEM_LENGTH 48

class TableMenu : public MenuScene {
    bool _finishing;

public:
    TableMenu(sf::RenderTarget *target);
    void setupMenu();
    void setupTable();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
