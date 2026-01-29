#include "gamemanager.h"

GameManager::GameManager(QGraphicsScene* scene) 
    : QObject(), scene(scene), food(nullptr), score(0) {
    
    setupGame();
}

void GameManager::setupGame() {
    createSnake();
    setupTimer();
    createFood();
}

void GameManager::createSnake() {
    createHead();
    createBody();
}

void GameManager::createHead() {
    Snake *snakeHead = new Snake(BodyType::HEAD);
    scene->addItem(snakeHead);
    snakeHead->setPos(200, 200); 
    snake.append(snakeHead);
}

void GameManager::createBody() {
    for (size_t i = 1; i < 4; i++)
    {
        Snake *snakeBody = new Snake(BodyType::BODY);
        scene->addItem(snakeBody);
        snakeBody->setPos(200 - i * 10, 200);
        snake.append(snakeBody);
    }
}

void GameManager::setupTimer() {
    connect(&timer, &QTimer::timeout, this, &GameManager::gameLoop);
    timer.start(100); // Game loop every 100 ms
}

void GameManager::gameLoop() {
    // Move each segment of the snake
    QPointF previousPosition = snake.first()->pos();
    for (auto segment : snake) {
        // Check for collisions
        if (segment == snake.first()) {
            QList<QGraphicsItem *> itemsAtHeadPos = scene->items(previousPosition);
            if (snake.first()->checkCollision(itemsAtHeadPos)) {
                timer.stop();
                return;
            }
        }      
        
        previousPosition = segment->move(previousPosition);
    }

    if (snake.first()->pos().x() == food->pos().x() && snake.first()->pos().y() == food->pos().y()) {
        Snake* newBodyPart = snake.last()->grow();
        scene->addItem(newBodyPart);
        snake.append(newBodyPart);

        score += 10;
        scoreChanged(score);

        do
        {
            food->generateNewPosition();
        } while (checkFoodCollision());
    }
}

void GameManager::keyPressed(QKeyEvent *event) {
    if (snake.isEmpty()) return;
    Direction newDirection;
    switch (event->key()) {
        case Qt::Key_W:
            newDirection = Direction::UP;
            break;
        case Qt::Key_S:
            newDirection = Direction::DOWN;
            break;
        case Qt::Key_A:
            newDirection = Direction::LEFT;
            break;
        case Qt::Key_D:
            newDirection = Direction::RIGHT;
            break;
        default:
            GameManager::keyPressed(event);
            return;
    }
    snake.first()->changeDirection(newDirection);
}

void GameManager::createFood() {
    food = new Food(470, 470);

    while (checkFoodCollision()) {
        food->generateNewPosition();
    }
    scene->addItem(food);
}

bool GameManager::checkFoodCollision() {
    for (auto segment : snake) {
        if (segment->pos().x() == food->pos().x() && segment->pos().y() == food->pos().y()) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}