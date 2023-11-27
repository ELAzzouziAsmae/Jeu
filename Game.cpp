#include "Game.h"
#include "Start.h"
void Game::initwindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "game 3", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}
void Game::initPlayer()
{
    this->player = new Player();
    this->player->setMovementSpeed(5.0f);
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
    this->lineSpawnTimerMax = 200.f;
    this->lineSpawnTimer = this->lineSpawnTimerMax;
    this->lineEnemies.push_back(new LineEnemy(rand() % this->window->getSize().x - 20.f,-100.f,sf::Color::Blue,3.f, 1.f ));
}


void Game::initSystems()
{
    this->points = 0;
    if (!pistolSoundBuffer.loadFromFile("sound/tir.wav")) {
        std::cerr << "Failed to load pistol sound!" << std::endl;
    }
    pistolSound.setBuffer(pistolSoundBuffer);
    

}

Game::Game()
{
    this->lineSpawnTimerMax = 200.f;
    this->lineSpawnTimer = 0.f;
    this->gui1 = new guiPlayerPoints();
    this->gui2 = new GameOver();
    this->gui3 = new guiplayerHpBar();
    soundManager.playBackgroundMusic();
    this->initwindow();
    this->initTextures();
    this->initPlayer();
    this->initGUID();
    this->initEnemies();
    this->initWord();
    this->initSystems();
    this->initBonus();

}

Game::~Game()
{
    delete this->player;
    delete this->window;
    for (auto& i : this->textures)
    {
        delete i.second;

    }
    for (auto* i : this->bullets)
    {
        delete i;
    }
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
       
        if (!this->gameManager.isPaused() && this->player->getHp() > 0)
        
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
        //
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
        {
            this->gameManager.togglePause();
        }
        //

    }
}




void Game::updateInput()
{
    //
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        this->gameManager.togglePause();
    }
    //

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->player->move(0.f, 1.f);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 2.f, this->player->getPos().y, 0.f, -1.f, 5.f));
        pistolSound.play();
    }

}void Game::updateColusion()
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

void Game::updateBullets()
{

    std::vector<Bullet*> bulletsToRemove;

    for (auto* bullet : this->bullets)
    {
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {

            bulletsToRemove.push_back(bullet);
        }
    }

    for (auto* bullet : bulletsToRemove)
    {
        auto it = std::find(this->bullets.begin(), this->bullets.end(), bullet);
        if (it != this->bullets.end())
        {
            this->bullets.erase(it);
            delete bullet; 
        }
    }

    for (auto* lineEnemy : this->lineEnemies)
    {
        for (auto* bullet : this->bullets)
        {
            if (lineEnemy->getBounds().intersects(bullet->getBounds()))
            {
            }
        }
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
   
}void Game::updateEnemies()
{
    float enemySpeed = 0.5f + (static_cast<float>(this->points) * 0.005f);
    float lineEnemySpeed = 0.5f + (static_cast<float>(this->points) * 0.002f);

    this->spawnTimer += enemySpeed;
    this->lineSpawnTimer += lineEnemySpeed;

    float playerHpLossPercentage = 0.3f;

    float lineEnemySpawnFrequency = 300.f; // Increase the frequency to reduce the appearance (adjust as needed)

    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f, enemySpeed));
        this->spawnTimer = 0.f;
    }

    if (this->lineSpawnTimer >= lineEnemySpawnFrequency)
    {
        this->lineEnemies.push_back(new LineEnemy(rand() % this->window->getSize().x - 20.f, -100.f, sf::Color::Blue, 3.f, 1));
        this->lineSpawnTimer = 0.f;
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

    for (auto* lineEnemy : this->lineEnemies)
    {
        lineEnemy->update();

        if (lineEnemy->getBounds().intersects(this->player->getBounds()))
        {
            int currentHp = this->player->getHp();
            int hpLoss = static_cast<int>(currentHp * playerHpLossPercentage);
            this->player->setHp(currentHp - hpLoss);
            auto it = std::find(this->lineEnemies.begin(), this->lineEnemies.end(), lineEnemy);
            if (it != this->lineEnemies.end())
            {
                this->lineEnemies.erase(it);
                delete lineEnemy;
            }
        }
    }
}




void Game::updateCombat()
{
    for (int i = 0; i < this->enemies.size(); i++) {
        for (size_t k = 0; k < this->bullets.size(); k++) {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) {
                this->points += this->enemies[i]->getPoints();
                                
                delete this->enemies[i];
                delete this->bullets[k];

                
                this->enemies.erase(this->enemies.begin() + i);
                this->bullets.erase(this->bullets.begin() + k);

                
                i--;
                k--;
                break; 
            }
        }
    }
}



void Game::update()
{
    sf::Time elapsed = clock.restart();

    float deltaTime = elapsed.asSeconds();
    totalElapsedTime += deltaTime;

    this->gui1->UpdateinitguiPlayerPoints(this->points, totalElapsedTime);

    std::cout << "Elapsed Time: " << deltaTime << std::endl;

    this->updateInput();
    this->player->update();

    this->updateColusion();
    this->updateBullets();
    this->updateEnemies();
    this->updateCombat();
    this->updateWorld();

    this->generateBonus(); 
    this->updateBonus();   


    this->handleBonusCollision();
    this->gui3->updateguiplayerHpBar(this->player->getHp(), this->player->getHpMax());

     for (auto* lineEnemy : this->lineEnemies)
     {
         lineEnemy->update();

     if (lineEnemy->getBounds().intersects(this->player->getBounds()))
     {
         this->player->gainPoints(1);

         auto it = std::find(this->lineEnemies.begin(), this->lineEnemies.end(), lineEnemy);
         if (it != this->lineEnemies.end())
         {
             this->lineEnemies.erase(it);
             delete lineEnemy;
         }
     }
     }

  

}

void Game::render()
{

    this->window->clear();
    this->renderWorld();
    this->player->render(*this->window);
    for (auto* bonus : bonuses)
    {
        this->window->draw(*bonus);

    }
    for (auto* bullet : this->bullets)
    {
        bullet->render(*this->window);

    }
    for (auto* enemy : this->enemies)
    {
        enemy->render(this->window);

    }
    for (auto* lineEnemy : this->lineEnemies)
    {
        lineEnemy->render(*this->window);
    }
    this->renderGUI();
    if (this->player->getHp() <= 0)
        this->window->draw(this->gui2->render());
    this->window->display();
}


void Game::initBonus()
{
    if (!bonusTexture.loadFromFile("Textures/cup.png"))
    {
        std::cout << "Error: Failed to load bonus texture" << std::endl;
    }
    bonusFrequency = 500; 
    bonusTimer = 0;
}

void Game::generateBonus()
{
    if (player->getHp() < player->getHpMax() && bonusTimer >= bonusFrequency)
    {
        float x = static_cast<float>(rand() % (window->getSize().x - 30)); 
        float y = static_cast<float>(-30); 
        Bonus* newBonus = new Bonus(x, y, bonusTexture);
        bonuses.push_back(newBonus);
        bonusTimer = 0; 
    }
}


void Game::updateWorld()
{
}


void Game::updateBonus()
{
    bonusTimer++;
    for (auto it = bonuses.begin(); it != bonuses.end();)
    {
        Bonus* bonus = *it;
        bonus->move(0, 2.0f); 
        if (bonus->getPosition().y > window->getSize().y)
        {
            delete bonus;
            it = bonuses.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Game::handleBonusCollision()
{
    for (auto it = bonuses.begin(); it != bonuses.end();)
    {
        Bonus* bonus = *it;
        if (bonus->isTouched(player->getBounds()))
        {
            this->player->setHp(this->player->getHp() + 10);
            delete bonus;
            it = bonuses.erase(it);
        }
        else
        {
            it++;
        }
    }
}






