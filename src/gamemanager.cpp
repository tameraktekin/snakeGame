#include "gamemanager.h"

GameManager::GameManager(QGraphicsScene* scene) 
    : QObject(), scene(scene), food(nullptr), score(0), scoreMilestone(Constants::Speed::SCORE_INIT_MILESTONE) {
    
    setupGame();
}

void GameManager::setupGame() {
    createSnake();
    setupTimer();
    createFood();
    setupSpeedHandling();
}

void GameManager::createSnake() {
    createHead();
    createBody();
}

void GameManager::createHead() {
    Snake *snakeHead = new Snake(BodyType::HEAD);
    scene->addItem(snakeHead);
    snakeHead->setPos(Constants::Snake::INITIAL_SNAKE_POS, Constants::Snake::INITIAL_SNAKE_POS); 
    snake.append(snakeHead);
}

void GameManager::createBody() {
    for (size_t i = 1; i < Constants::Snake::INITIAL_SNAKE_LENGTH; i++)
    {
        Snake *snakeBody = new Snake(BodyType::BODY);
        scene->addItem(snakeBody);
        snakeBody->setPos(Constants::Snake::INITIAL_SNAKE_POS - i * Constants::MOVE_DISTANCE, Constants::Snake::INITIAL_SNAKE_POS);
        snake.append(snakeBody);
    }
}

void GameManager::setupTimer() {
    connect(&timer, &QTimer::timeout, this, &GameManager::gameLoop);
    timer.start(Constants::Speed::INITIAL_SPEED); // Game loop every 100 ms
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
                gameOver(score);
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
    food = new Food(Constants::Grid::WIDTH, Constants::Grid::HEIGHT);

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

void GameManager::setupSpeedHandling() {
    connect(this, &GameManager::scoreChanged, 
        this, &GameManager::handleSpeedIncrease);
}

bool GameManager::checkScoreMilestone() {
    if (score % scoreMilestone == 0) {
        scoreMilestone *= Constants::Speed::SCORE_MILESTONE_MULTIPLIER;
        return true;
    }
    else {
        return false;
    }
}

void GameManager::handleSpeedIncrease() {
    if (checkScoreMilestone())
    {
        int currentInterval = timer.interval();
        int newInterval = currentInterval - Constants::Speed::SPEED_INCREMENT;
        if (newInterval < Constants::Speed::MIN_SPEED) {
            newInterval = Constants::Speed::MIN_SPEED;
        }
        timer.setInterval(newInterval);
    }
}
