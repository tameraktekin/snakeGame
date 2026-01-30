#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include "constants.h"

/**
 * @class AudioManager
 * @brief Manages audio playback for the Snake game.
 */
class AudioManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the AudioManager and initializes sound effects.
     * @param parent Pointer to the parent QObject (default is nullptr).
     */
    AudioManager(QObject *parent = nullptr);

    /**
     * @brief Destructor to clean up resources.
     */
    ~AudioManager();

public slots:
    /**
     * @brief Plays the sound effect for eating food.
     */
    void playEatSound();

    /**
     * @brief Plays the sound effect for game over.
     */
    void playGameOverSound();

private:
    /**
     * @brief Sound effect player for eating food.
     */
    QSoundEffect *soundEffectPlayerEat;

    /**
     * @brief Sound effect for game over.
     */
    QSoundEffect *soundEffectGameOver;

    void initSoundEffects();
};

#endif // AUDIOMANAGER_H