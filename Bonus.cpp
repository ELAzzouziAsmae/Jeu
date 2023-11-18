#include "Bonus.h"

Bonus::Bonus(float x, float y, const sf::Texture& texture)
{
    this->setTexture(texture);
    this->setPosition(x, y);
}

bool Bonus::isTouched(const sf::FloatRect& playerBounds)
{
    sf::FloatRect bonusBounds = this->getGlobalBounds();
    return bonusBounds.intersects(playerBounds);
}
