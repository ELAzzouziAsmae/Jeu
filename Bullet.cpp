#include "Bullet.h"




Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float mouvement_speed)
{
    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->mouvementSpeed = mouvement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{

    return this->shape.getGlobalBounds();
}

void Bullet::update()
{
    this->shape.move(this->mouvementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
