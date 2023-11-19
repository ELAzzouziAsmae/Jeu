#pragma once
#include "player.h"
#include <string>
#include <sstream>
#include "Bullet.h"
#include "Enemy.h"
#include "guiPlayerPoints.h"
#include "GameOver.h"
#include "guiplayerHpBar.h"
#include "Bonus.h"
#include "SoundManager.h"
#include <SFML/Audio.hpp>

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
    SoundManager soundManager;
    sf::Sound pistolSound;
    sf::SoundBuffer pistolSoundBuffer;

 
    Player* player;
    std::vector<Bonus*> bonuses;
    sf::Texture bonusTexture;
    int bonusFrequency; // Adjust this value based on enemy speed
    int bonusTimer; // Keep track of time to determine when to spawn bonuses

    guiPlayerPoints* gui1;
    GameOver* gui2;
    guiplayerHpBar* gui3;



    std::vector<Enemy*> enemies;
   


    float spawnTimer;
    float spawnTimerMax;
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
 
    void renderGUI();
    void renderWorld();
    void updateEnemies();
    void updateCombat();

    void update();
    void render();
    void initBonus();
    void updateBonus();
    void handleBonusCollision();
    void generateBonus();

};

