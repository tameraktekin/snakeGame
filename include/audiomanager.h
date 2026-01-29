#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include "constants.h"

class AudioManager : public QObject
{
    Q_OBJECT

public:
    AudioManager(QObject *parent = nullptr);
    ~AudioManager();

public slots:
    void playEatSound();
    void playGameOverSound();

private:
    QSoundEffect *soundEffectPlayerEat;
    QSoundEffect *soundEffectGameOver;

    void initSoundEffects();
};

#endif // AUDIOMANAGER_H