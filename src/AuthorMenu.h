#pragma once

#include <SFML/Graphics.hpp>

#include "MenuScene.h"

#define AUTHOR_MENU_ITEM_COUNT 11
#define AUTHOR_MENU_ITEM_LENGTH 60

class AuthorMenu : public MenuScene {
    bool _finishing;

public:
    AuthorMenu(sf::RenderTarget *target);
    void setupMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
