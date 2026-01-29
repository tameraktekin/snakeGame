#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include "snake.h"
#include "food.h"
#include "constants.h"


class GameManager : public QObject {
    Q_OBJECT

public:
    GameManager(QGraphicsScene* scene);
    void keyPressed(QKeyEvent *event);

signals:
    void scoreChanged(int newScore);

private slots:
    void gameLoop();

private:
    QGraphicsScene* scene;
    QList<Snake*> snake;
    Food* food;
    QTimer timer;
    int score;

    void setupGame();
    void setupTimer();
    void createSnake();
    void createHead();
    void createBody();
    void createFood();
    bool checkFoodCollision();
};

#endif // GAMEMANAGER_H