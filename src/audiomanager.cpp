#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent)
    : QObject(parent) {
    initSoundEffects();
}

AudioManager::~AudioManager() {
    delete soundEffectPlayerEat;
    delete soundEffectGameOver;
}

void AudioManager::initSoundEffects() {
    soundEffectPlayerEat = new QSoundEffect(this);
    soundEffectPlayerEat->setSource(QUrl::fromLocalFile(Constants::Audio::SOUND_EFFECT_EAT));
    soundEffectPlayerEat->setVolume(0.5f); // Set volume (0.0 to 1.0)

    soundEffectGameOver = new QSoundEffect(this);
    soundEffectGameOver->setSource(QUrl::fromLocalFile(Constants::Audio::SOUND_EFFECT_GAME_OVER));
    soundEffectGameOver->setVolume(0.5f); // Set volume (0.0 to 1.0)
}

void AudioManager::playEatSound() {
    if (soundEffectPlayerEat->isLoaded()) {
        soundEffectPlayerEat->play();
    }
}

void AudioManager::playGameOverSound() {
    if (soundEffectGameOver->isLoaded()) {
        soundEffectGameOver->play();
    }
}