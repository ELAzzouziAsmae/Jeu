#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include <string>
#include <sstream>
class guiPlayerPoints
{
private:
    sf::Font font;
    sf::Text poitText1;
    sf::Text poitText2;





public:
    guiPlayerPoints();
    virtual ~guiPlayerPoints();
    void initguiPlayerPoints();
    void UpdateinitguiPlayerPoints(unsigned points, float totalElapsedTime);

    std::pair<sf::Text, sf::Text> render() const;
};

