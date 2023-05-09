#pragma once

#include <SFML/Graphics.hpp>

#include "RacePlayer.hpp"
#include "RectangleShape2.h"
#include "Scene.h"
#include "TileMap.hpp"

#define RACE_DELAY 10000
#define RACE_PARTICIPANTS 3
#define RACE_PIXEL_SCALE 2.5f
#define RACE_TRACK_INDENT 40.f
#define RACE_TRACK_ITERATIONS 50
#define RACE_TRACK_ROUNDNESS 0.5f
#define RACE_TRACK_SIZE_X 510.f
#define RACE_TRACK_SIZE_Y 270.f

struct Player {
    RacePlayer racer;
    size_t bound;
    float tick;

    Player() : bound(0), tick(0.f) {
        racer.setSpeed(1.f);
    }
};

class RaceScene : public Scene {
    sf::Vector2f _size;
    bool _finishing;

    TileMap _layers[3];
    RectangleShape2 _tracks[RACE_PARTICIPANTS];
    Player _players[RACE_PARTICIPANTS];

    int _raceDelay;

public:
    RaceScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setup();
    void setupTileMap(TileMap &tileMap, const std::string &tileset,
                      const int *layer);
    void setupTrack(RectangleShape2 &track, const sf::Vector2f &size);
    void setupPlayer(Player &player);
    void syncTrackVertices(RectangleShape2 &dest, const RectangleShape2 &source);

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
};
