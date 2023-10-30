#ifndef BONUS_ENEMY_H
#define BONUS_ENEMY_H

#include <SFML/Graphics.hpp>

class BonusEnemy
{
private:
    sf::RectangleShape shape;
    int points;

public:
    BonusEnemy(float pos_x, float pos_y, sf::Color color, int bonusPoints);
    virtual ~BonusEnemy();
    const sf::FloatRect getBounds() const;
    const int& getPoints() const;
    void update();
    void render(sf::RenderTarget* target);
};

#endif
