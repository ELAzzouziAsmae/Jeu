#include "SoundManager.h"

SoundManager::SoundManager() {
    // Chargez ici les fichiers audio au sein du constructeur.
    if (!backgroundMusic.openFromFile("sound/sound.wav")) {
        // Gérer l'erreur : impossible de charger la musique de fond.
    }

    if (!soundBuffer.loadFromFile("sound/sound.wav")) {
        // Gérer l'erreur : impossible de charger l'effet sonore.
    }

    soundEffect.setBuffer(soundBuffer);
}

void SoundManager::playBackgroundMusic() {
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

void SoundManager::playSoundEffect() {
    soundEffect.play();
}
