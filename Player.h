#include "player.h"

void Player::initVariables()
{
    this->mouvementSpeed = 2.f;
    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;
    this->hpMax = 100;
    this->hp = this->hpMax;
}

void Player::initTexture()
{
    if (!this->texture.loadFromFile("Textures/ship.png"))
        std::cout << "ERROR" << "\n";
}

void Player::initSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.3f, 0.3f);
}

Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}
void Player::gainPoints(int points)
{
    this->points += points;
    this->hp += points; // Ajoutez les points à la barre de points (hp)


}
const int& Player::getHp() const
{
    return this->hp;

}

const int& Player::getHpMax() const
{
    return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
    this->hp = hp;
}

void Player::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->mouvementSpeed * dirX, this->mouvementSpeed * dirY);
}

const bool Player::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}



void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
