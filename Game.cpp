#include "Game.h"

void Game::initwindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "game 3", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}







void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initGUID()
{
    this->gui1->initguiPlayerPoints();
    this->gui2->initGameOver(this->window->getSize().x, this->window->getSize().y);
    this->gui3->initguiplayerHpBar();
}

void Game::initWord()
{

    if (!this->worldBackgroundText.loadFromFile("Textures/bck.jpeg"))
    {
        std::cout << "error:: failed picture load";
    }
    this->worldBackground.setTexture(this->worldBackgroundText);
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}


void Game::initSystems()
{
    this->points = 0;
}

Game::Game()
{
    this->initwindow();
   

    this->initPlayer();
    this->initGUID();
    this->initEnemies();
    this->initWord();
    this->initSystems();
    


}

Game::~Game()
{
    delete this->player;
    delete this->window;
    for (auto* i : this->enemies)
    {
        delete i;
    }

}

void Game::run()
{
    Start startScreen(this->window);
    while (this->window->isOpen() && !startScreen.isGameStarted())
    {
        startScreen.handleEvents();
        startScreen.render();
    }

    while (this->window->isOpen())
    {
        this->updatePollEvents();
        if (this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

void Game::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();

    }
}




void Game::updateInput()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->player->move(0.f, 1.f);

}

void Game::updateWorld()
{
}

void Game::updateColusion()
{
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
    if (this->player->getBounds().top < 100.f)
    {
        this->player->setPosition(this->player->getBounds().left, 100.f);
    }
    if (this->player->getBounds().left > this->window->getSize().x - 100.f)
    {
        this->player->setPosition(this->window->getSize().x - 100.f, this->player->getBounds().top);
    }
    if (this->player->getBounds().top > this->window->getSize().y - 100.f)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - 100.f);
    }
}




void Game::renderGUI()
{
    std::pair<sf::Text, sf::Text> textPair = this->gui1->render();
    sf::Text text1 = textPair.first;
    sf::Text text2 = textPair.second;

    std::pair<sf::RectangleShape, sf::RectangleShape> hpBars = this->gui3->render();
    sf::RectangleShape playerHpBar = hpBars.first;
    sf::RectangleShape playerHpBarBack = hpBars.second;


    this->window->draw(text1);
    this->window->draw(text2);
    this->window->draw(playerHpBarBack);
    this->window->draw(playerHpBar);
}


void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}


void Game::updateEnemies()
{///////////////////////////////////////////
    this->spawnTimer += 0.3f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.f;


    }


    unsigned counter = 0;
    for (auto* enemy : this->enemies)
    {
        enemy->update();
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);

        }
        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());

            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);

        }
        ++counter;
    }





}




void Game::update()
{

    this->updateInput();
    this->player->update();

    this->updateColusion();
 
    this->updateCombat();
    this->updateWorld();




  

}

void Game::render()
{

    this->window->clear();
    this->renderWorld();
    this->player->render(*this->window);
   

    this->renderGUI();
    if (this->player->getHp() <= 0)
        this->window->draw(this->gui2->render());

}






void Game::update()
{

    this->updateInput();
   
    this->updateColusion();
    
    this->updateEnemies();
    this->updateCombat();
    this->updateGUI();
    this->updateWorld();


}

void Game::render()
{

    this->window->clear();
    this->renderWorld();

    this->player->render(*this->window);
    for (auto* bullet : this->bullets)
    {
        bullet->render(*this->window);

    }
    for (auto* enemy : this->enemies)
    {
        enemy->render(this->window);

    }
    this->renderGUI();
    if (this->player->getHp() <= 0)
        this->window->draw(this->gameOverText);
    this->window->display();

}