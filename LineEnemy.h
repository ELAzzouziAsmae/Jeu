#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class LineEnemy
{
private:
    sf::RectangleShape shape;
    sf::Color color;
    float speed;
    int points;

public:
    LineEnemy(float startX, float startY, sf::Color enemyColor, float enemySpeed, int enemyPoints);
    void update();
    void render(sf::RenderTarget& target);
    const sf::FloatRect getBounds() const;
};
