#include "Start.h"
#include <iostream>

Start::Start(sf::RenderWindow* window)
{
    this->window = window;
    this->gameStarted = false;

    if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
        std::cerr << "Failed to load font!" << std::endl;

    this->startText.setFont(this->font);
    this->startText.setCharacterSize(60);
    this->startText.setFillColor(sf::Color::White);
    this->startText.setString("C lick    Start   to    begin");
    this->startText.setPosition(
        window->getSize().x / 2.f - this->startText.getGlobalBounds().width / 2.f,
        window->getSize().y / 2.f - this->startText.getGlobalBounds().height / 2.f);
}

Start::~Start()
{
}

bool Start::isGameStarted() const
{
    return this->gameStarted;
}

void Start::handleEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            this->window->close();
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (this->startText.getGlobalBounds().contains(sf::Vector2f(e.mouseButton.x, e.mouseButton.y)))
                {
                    this->gameStarted = true;
                }
            }
        }
    }
}

void Start::update()
{
}

void Start::render()
{
    this->window->clear();
    this->window->draw(this->startText);
    this->window->display();
}
