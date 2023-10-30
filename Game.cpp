#include "Game.h"




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
}

void Game::initGUID()
{
    if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
    std::cout << "error loaded font";
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over !");
    this->gameOverText.setPosition(
    this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
    
        
this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    this->poitText.setFont(this->font);
    this->poitText.setCharacterSize(20);
    this->poitText.setFillColor(sf::Color::White);
    this->poitText.setString("test");

    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    

}

void Game::initWord()
{ 
    
    if (!this->worldBackgroundText.loadFromFile("Textures/background.jpg"))
    {
        std::cout << "error:: failed picture load";
    }
    this->worldBackground.setTexture(this->worldBackgroundText);
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;

    // Ajoutez les LineEnemy
    this->lineEnemies.push_back(new LineEnemy(
        rand() % this->window->getSize().x - 20.f,
        -100.f,
        sf::Color::Blue, 
        3.f, // Largeur
        1.f // Hauteur
    ));
    // Ajoutez autant de LineEnemy que nécessaire

}

void Game::initSystems()
{
    this->points = 0;
}

Game::Game()
{
    
    this->initwindow();
    this->initTextures();
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
    for (auto &i : this->textures )
    {
        delete i.second;

    }
    for(auto *i : this->bullets)
    {
        delete i;
    }
    for (auto* i : this->enemies)
    {
        delete i;
    }
}

void Game::run()
{   while(this->window->isOpen())
{
    this->updatePollEvents();
    if(this->player->getHp() > 0)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left ) && this->player->canAttack()) {
        this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x +this->player->getBounds().width/2.f, this->player->getPos().y, 0.f, -1.f, 5.f));

    }
    
}

void Game::updateWorld()
{
}

void Game::updateColusion()
{
    if (this->player->getBounds().left < 0.f )
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
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
    // Create a new vector to store bullets to be removed
    std::vector<Bullet*> bulletsToRemove;

    for (auto* bullet : this->bullets)
    {
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            // Instead of deleting and erasing in the loop, mark for removal
            bulletsToRemove.push_back(bullet);
        }
    }

    // Remove the marked bullets from the original vector
    for (auto* bullet : bulletsToRemove)
    {
        auto it = std::find(this->bullets.begin(), this->bullets.end(), bullet);
        if (it != this->bullets.end())
        {
            this->bullets.erase(it);
            delete bullet; // Delete the removed bullet
        }
    }
    // Collision entre les balles et les LineEnemy
std::vector<LineEnemy*> lineEnemiesToRemove;

for (auto* lineEnemy : this->lineEnemies)
{
    for (auto* bullet : this->bullets)
    {
        if (lineEnemy->getBounds().intersects(bullet->getBounds()))
        {
            // Le joueur a touché le LineEnemy avec une balle, ajoutez des points
            this->player->gainPoints(1);

            // Marquez le LineEnemy pour suppression
            lineEnemiesToRemove.push_back(lineEnemy);
        }
    }

    // Collision entre le joueur et le LineEnemy
    if (lineEnemy->getBounds().intersects(this->player->getBounds()))
    {
        // Le joueur a atteint le LineEnemy, ajoutez des points à la barre de points
        int currentHp = this->player->getHp();
        this->player->setHp(currentHp + 1);

        // Supprimez le LineEnemy
        auto it = std::find(this->lineEnemies.begin(), this->lineEnemies.end(), lineEnemy);
        if (it != this->lineEnemies.end())
        {
            this->lineEnemies.erase(it);
            delete lineEnemy;
        }
    }

}

// Supprimez les LineEnemy marqués pour suppression
for (auto* lineEnemy : lineEnemiesToRemove)
{
    auto it = std::find(this->lineEnemies.begin(), this->lineEnemies.end(), lineEnemy);
    if (it != this->lineEnemies.end())
    {
        this->lineEnemies.erase(it);
        delete lineEnemy;
    }
}

}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "Points: " << this->player->getHp();
    this->poitText.setString(ss.str());
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));



}

void Game::renderGUI()
{
    this->window->draw(this->poitText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::updateEnemies()
{
        this->spawnTimer += 0.5f;
        if (this->spawnTimer >= this->spawnTimerMax)
        {
            this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
            this->lineEnemies.push_back(new LineEnemy(rand() % this->window->getSize().x - 20.f, -100.f, sf::Color::Blue, 3.f, 1));
            this->spawnTimer = 0.f;
        }

        unsigned counter = 0;
        for (auto* enemy : this->enemies)
        {
            enemy->update();
            enemy->render(this->window);
            if (enemy->getBounds().top > this->window->getSize().y)
            {
                delete enemy;
                this->enemies.erase(this->enemies.begin() + counter);
            }
            else if (enemy->getBounds().intersects(this->player->getBounds()))
            {
                this->player->loseHp(enemy->getDamage());
                delete enemy;
                this->enemies.erase(this->enemies.begin() + counter);
            }
            ++counter;
        }
    
        for (auto* lineEnemy : this->lineEnemies)
        {
            lineEnemy->update();
        }
    
    
}

void Game::updateCombat()
{
    for (int i = 0; i < this->enemies.size(); i++) {
        for (size_t k = 0; k < this->bullets.size(); k++) {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) {
                this->points += this->enemies[i]->getPoints();
                // Mark the enemy and bullet for deletion
                delete this->enemies[i];
                delete this->bullets[k];

                // Remove the marked enemy and bullet
                this->enemies.erase(this->enemies.begin() + i);
                this->bullets.erase(this->bullets.begin() + k);

                // Decrement i and k to recheck the current index
                i--;
                k--;
                break; // Exit the inner loop since the bullet can only hit one enemy
            }
        }
    }

}


void Game::update()
{
    this->updateInput();
    this->player->update();
    this->updateColusion();
    this->updateBullets();
    this->updateEnemies();
    this->updateCombat();
    this->updateGUI();
    this->updateWorld();
    for (auto* lineEnemy : this->lineEnemies)
    {
        lineEnemy->update();

        // Collision entre le joueur et le LineEnemy
        if (lineEnemy->getBounds().intersects(this->player->getBounds()))
        {
            // Le joueur a atteint le LineEnemy, ajoutez des points
            this->player->gainPoints(1);

            // Supprimez le LineEnemy
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
        this->window->draw(this->gameOverText);
    this->window->display();
}


