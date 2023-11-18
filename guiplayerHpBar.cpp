#include "guiplayerHpBar.h"

guiplayerHpBar::guiplayerHpBar()
{
}

guiplayerHpBar::~guiplayerHpBar()
{
}

void guiplayerHpBar::initguiplayerHpBar()
{
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void guiplayerHpBar::updateguiplayerHpBar(int hp, int hpmax)
{
    float hpPercent = static_cast<float>(hp) / hpmax;
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

std::pair<sf::RectangleShape, sf::RectangleShape> guiplayerHpBar::render()
{
    return std::make_pair(this->playerHpBar, this->playerHpBarBack);
}

