#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "fragrect.hpp"
#include "menucontainer.h"
#include "scene.h"

#define MENU_BORDER_MARGIN 10.f
#define MENU_BORDER_WIDTH 5.f
#define MENU_CHAR_DRAWN_TIMEOUT 7000
#define MENU_COLOR_OFFSET_STEP 0.001f
#define MENU_COLOR_OFFSET_TIMEOUT 1000
#define MENU_ITEM_FONT_SIZE 14
#define MENU_ITEM_INDENT 2.f

class MenuScene : public Scene {
    sf::RectangleShape _background;
    FragmentRectangleShape _r1, _r2, _r3, _r4;
    sf::Shader _borderShader;

    int _colorOffsetTimeout;
    float _colorOffset;

    int _nextCharTimeout;

public:
    MenuScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

protected:
    MenuContainer _menu;
    sf::Font _itemFont;

    void setup(std::size_t cols, std::size_t rows);

private:
    void setupBorders(const sf::Vector2f &size, const sf::Vector2f &center);
    bool setupMenu(float menuWidth, std::size_t rows, const sf::Vector2f &center);
};
