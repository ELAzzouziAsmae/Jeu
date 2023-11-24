#include "LineEnemy.h"

LineEnemy::LineEnemy(float startX, float startY, sf::Color enemyColor, float enemySpeed, int enemyPoints)
    : color(enemyColor), speed(enemySpeed), points(enemyPoints)
{
    this->shape.setSize(sf::Vector2f(20.f, 5.f));
    this->shape.setPosition(startX, startY);
    this->shape.setFillColor(this->color);
}

void LineEnemy::update()
{
    this->shape.move(0.f, this->speed);
}

void LineEnemy::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}

const sf::FloatRect LineEnemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}
