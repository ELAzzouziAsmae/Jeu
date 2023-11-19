#include "guiPlayerPoints.h"

guiPlayerPoints::guiPlayerPoints()
{
    this->initguiPlayerPoints();

}

guiPlayerPoints::~guiPlayerPoints()
{
}

void guiPlayerPoints::initguiPlayerPoints()
{
    if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
        std::cout << "error loaded font";
    this->poitText1.setFont(this->font);
    this->poitText1.setCharacterSize(20);
    this->poitText1.setFillColor(sf::Color::White);
    sf::Vector2f position(680.0f, 10.0f);
    this->poitText1.setString("Points");
    this->poitText1.setPosition(position);

    this->poitText2.setFont(this->font);
    this->poitText2.setCharacterSize(25);
    this->poitText2.setFillColor(sf::Color::Red);
    sf::Vector2f position1(760.0f, 7.0f);
    this->poitText2.setPosition(position1);
}



void guiPlayerPoints::UpdateinitguiPlayerPoints(unsigned points)
{
    std::stringstream ss;
    ss << points;
    this->poitText2.setString(ss.str());
}

std::pair<sf::Text, sf::Text> guiPlayerPoints::render()
{
    return std::make_pair(this->poitText1, this->poitText2);
}

