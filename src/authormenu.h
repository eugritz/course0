#pragma once

#include <SFML/Graphics.hpp>

#include "menuscene.h"

#define AUTHOR_MENU_ITEM_COUNT 9
#define AUTHOR_MENU_ITEM_LENGTH 50

class AuthorMenu : public MenuScene {
    bool _finishing;

public:
    AuthorMenu(sf::RenderTarget *target);
    void setupMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
