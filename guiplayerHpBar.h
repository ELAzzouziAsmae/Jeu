#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include <string>
#include <sstream>
class guiplayerHpBar
{
private:
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
public:
    guiplayerHpBar();
    virtual ~guiplayerHpBar();
    void initguiplayerHpBar();
    void updateguiplayerHpBar(int hp, int hpmax);
    std::pair<sf::RectangleShape, sf::RectangleShape> render();
};

