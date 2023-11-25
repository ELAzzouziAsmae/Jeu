// GameManager.cpp

#include "GameManager.h"

GameManager::GameManager() : paused(false)
{
}

GameManager::~GameManager()
{
}

bool GameManager::isPaused() const
{
    return paused;
}

void GameManager::togglePause()
{
    paused = !paused;
}
