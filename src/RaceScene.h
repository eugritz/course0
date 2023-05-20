#pragma once

#include <SFML/Graphics.hpp>

#include "RacePlayer.h"
#include "RectangleShape2.h"
#include "Resources.hpp"
#include "Scene.h"
#include "TileMap.h"
#include "Timer.h"

#define RACE_COLOR_SWITCH_DELAY 600000
#define RACE_DELAY 10000
#define RACE_PLAYERS 3
#define RACE_PLAYER_OFFSET_Y -15.f
#define RACE_PLAYER_OFFSET_START -20
#define RACE_PIXEL_SCALE 2.5f
#define RACE_TIMER_DURATION 3
#define RACE_TRACK_INDENT 40.f
#define RACE_TRACK_ITERATIONS 50
#define RACE_TRACK_ROUNDNESS 0.5f
#define RACE_TRACK_SIZE_X 510.f
#define RACE_TRACK_SIZE_Y 270.f

struct Player {
    RacePlayer racer;
    sf::Text nameLabel;
    PlayerType type;
    size_t bound;
    size_t start;
    float tick;

    Player() : bound(0), tick(0.f) {
        racer.setSpeed(1.f);
    }
};

class RaceScene : public Scene {
    sf::Vector2f _size;
    bool _finishing;
    size_t _selected;
    SharedResource<sf::Font> _nameFont;

    TileMap _layers[3];
    RectangleShape2 _tracks[RACE_PLAYERS];
    Player _players[RACE_PLAYERS];
    Timer _timer;

    sf::Text _finishNameLabel, _finishLabel;
    std::vector<size_t> _finishers;
    bool _hasWinner;

    int _colorSwitchDelay;
    int _raceDelay;

public:
    RaceScene(sf::RenderTarget *target, PlayerOption players[RACE_PLAYERS],
              size_t selected);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setup();
    void setupOptions(PlayerOption options[RACE_PLAYERS]);
    void setupTileMap(TileMap &tileMap, const std::string &tileset,
                      const int *layer);
    void setupTrack(RectangleShape2 &track, const sf::Vector2f &size);
    void setupPlayer(Player &player, RectangleShape2 &track);
    void syncTrackVertices(RectangleShape2 &dest, const RectangleShape2 &source);

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
    void onFinishPassed();

    void updatePlayerPosition(Player &player, const RectangleShape2 &track);
};
