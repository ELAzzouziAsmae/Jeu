#include "GameOver.h"


GameOver::GameOver()
{
   
}

GameOver::~GameOver()
{
}



void GameOver::initGameOver(unsigned int x, unsigned int y)
{
    if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
        std::cout << "error loaded font";
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(100);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over !");
    this->gameOverText.setPosition(
        x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

}

sf::Text GameOver::render()
{
    return this->gameOverText;
}
