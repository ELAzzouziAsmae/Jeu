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
    if (!this->font.loadFromFile("Fonts/Dosis-VariableFont_wght.TTF"))
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
    sf::Vector2f position1(660.0f, 32.0f);
    this->poitText2.setPosition(position1);

}



void guiPlayerPoints::UpdateinitguiPlayerPoints(unsigned points, float totalElapsedTime) {
    std::ostringstream ss;
    ss << "Points: " << points;
    poitText1.setString(ss.str());

    int minutes = static_cast<int>(totalElapsedTime) / 60;
    int seconds = static_cast<int>(totalElapsedTime) % 60;

    std::ostringstream timeSS;
    timeSS << "Time: " << minutes << "m " << seconds << "s";
    poitText2.setString(timeSS.str());
    std::cout << "Elapsed Time in GUI: " << totalElapsedTime << std::endl;
}

std::pair<sf::Text, sf::Text> guiPlayerPoints::render() const {

    return std::make_pair(poitText1, poitText2);
}
