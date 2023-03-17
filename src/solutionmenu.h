#pragma once

#include <SFML/Graphics.hpp>

#include "menuscene.h"

#define SOLUTION_MENU_ITEM_COUNT 12
#define SOLUTION_MENU_ITEM_LENGTH 44

class SolutionMenu : public MenuScene {
    bool _finishing;

public:
    SolutionMenu(sf::RenderTarget *target);
    void setupMenu();
    void bisectMethodMenu();
    void chordsMethodMenu();

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    float bisect(float a, float b, float e, std::function<float(float)> func);
    float chords(float x0, float x1, float e, std::function<float(float)> func);
};
