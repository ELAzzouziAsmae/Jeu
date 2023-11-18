#pragma once
#include "player.h"
#include <string>
#include <sstream>
#include "Enemy.h"
#include<map>

class Game
{
private:

    sf::RenderWindow* window;
    Player* player;


    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
   


    float spawnTimer;
    float spawnTimerMax;
    void initwindow();
    void initPlayer();
    void initGUID();

    void initSystems();


    void initWord();
    void initEnemies();

public:
    Game();
    virtual ~Game();
    void run();
    void updatePollEvents();
    void updateInput();
    void updateWorld();
    void updateColusion();

 
    void renderGUI();
    void renderWorld();
    void updateEnemies();
    void update();
    void render();

};

