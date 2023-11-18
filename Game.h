#pragma once
#include "player.h"
#include <string>
#include <sstream>
#include "Bullet.h"
#include "Enemy.h"
#include<map>

class Game
{
private:

    sf::RenderWindow* window;
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    sf::Texture worldBackgroundText;
    sf::Sprite worldBackground;
    unsigned points;
    Player* player;
    sf::Texture bonusTexture;


    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
   


    float spawnTimer;
    float spawnTimerMax;
    void initwindow();
    void initTextures();
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
    void updateBullets();

 
    void renderGUI();
    void renderWorld();
    void updateEnemies();
    void updateCombat();

    void update();
    void render();

};

