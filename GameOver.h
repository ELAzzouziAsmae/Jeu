#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include <string>
#include <sstream>
class GameOver
{
private:
    sf::Text gameOverText;
    sf::Font font;
public:
    GameOver();
    virtual ~GameOver();
    sf::Text render();
    void initGameOver(unsigned int x, unsigned int y);
};

