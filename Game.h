#pragma once
#include "player.h"
#include <string>
#include <sstream>
#include<map>

class Game
{
private:


    Player* player;







    float spawnTimer;
    float spawnTimerMax;
 
    void initPlayer();
    void initGUID();

    void initSystems();

public:
    Game();
    virtual ~Game();
    void run();
    void updateInput();
    void updateColusion();

 
    void renderGUI();

    void update();
    void render();

};

