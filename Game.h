#pragma once
#include "player.h"
#include <string>
#include <sstream>
#include "Bullet.h"
#include "Enemy.h"
#include "LineEnemy.h"
#include<map>

class Game
{
private:
    sf::RenderWindow* window;
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    sf::Font font;
    sf::Text poitText;
    sf::Texture worldBackgroundText;
    sf::Sprite worldBackground;
    unsigned points;
    unsigned maxPoints;  // Variable pour le nombre maximal de points possibles
    std::vector<LineEnemy*> lineEnemies;

    Player* player;

    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    sf::Text gameOverText;

    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
    void initwindow();
    void initTextures();
    void initPlayer();
    void initGUID(); 
    void initWord();
    void initEnemies();
    void initSystems();

public:
    Game();
    virtual ~Game();
    void run(); 
    void updatePollEvents();
    void updateInput();
    void updateWorld();
    void updateColusion();
    void updateBullets();
    void updateGUI();
    void renderGUI();
    void renderWorld();
    void updateEnemies();
    void updateCombat();
    void update();
    void render();
};

