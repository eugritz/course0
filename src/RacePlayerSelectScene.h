#pragma once

#include <SFML/Graphics.hpp>

#include <random>

#include "Scene.h"
#include "Scroll.hpp"

const sf::String NAMES[] = {
    "John", "Doe", "Jack", "Sparrow", "James", "Bond", "Tony", "Stark",
    "Peter", "Parker", "John", "Wick", "Jabba", "the Hutt", "Lara", "Croft",
    "Scrudge", "McDuck"
};

class RacePlayerSelectScene : public Scene {
    bool _finishing;
    Scroll _scroll;
    sf::String _name;

    std::mt19937 gen;

public:
    RacePlayerSelectScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    sf::String generateName();

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
};
