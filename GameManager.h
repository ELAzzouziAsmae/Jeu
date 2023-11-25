// GameManager.h

#pragma once

class GameManager
{
private:
    bool paused;

public:
    GameManager();
    ~GameManager();

    bool isPaused() const;
    void togglePause();
};
