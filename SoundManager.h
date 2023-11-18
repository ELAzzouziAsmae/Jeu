#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>

class SoundManager {
public:
    SoundManager();
    void playBackgroundMusic();
    void playSoundEffect();
    // Vous pouvez ajouter d'autres fonctions selon vos besoins.

private:
    sf::Music backgroundMusic;
    sf::SoundBuffer soundBuffer;
    sf::Sound soundEffect;
};

#endif
