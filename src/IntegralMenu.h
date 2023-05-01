#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "MenuScene.h"

#define INTEGRAL_MENU_ITEM_COUNT 12
#define INTEGRAL_MENU_ITEM_LENGTH 44

class IntegralMenu : public MenuScene {
    bool _finishing;

public:
    IntegralMenu(sf::RenderTarget *target);
    void setupMenu();
    void rectanglesMethodMenu();
    void trapezoidMethodMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    float rectangle(float a, float b, float n,
                    std::function<float(float)> func);
    float trapezoid(float a, float b, float n,
                    std::function<float(float)> func);
};
