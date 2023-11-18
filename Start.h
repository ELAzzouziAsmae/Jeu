#pragma once
#include <SFML/Graphics.hpp>

class Start
{
private:
    sf::RenderWindow* window;
    sf::Text startText;
    sf::Font font;
    bool gameStarted;

public:
    Start(sf::RenderWindow* window);
    virtual ~Start();
    bool isGameStarted() const;
    void handleEvents();
    void update();
    void render();
};