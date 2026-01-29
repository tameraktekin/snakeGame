#include "mainwindow.h"
#include "./ui_mainwindow.h" // Created automatically by CMake/UIC

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    setupScene();
    setupGame();
    score = 0;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupScene() {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 470, 470); // Set scene size

    ui->gameView->setScene(scene);
    ui->gameView->setRenderHint(QPainter::Antialiasing);
    ui->gameView->setFocusPolicy(Qt::StrongFocus);
    ui->gameView->setFocus();
}

void MainWindow::setupGame() {
    createSnake();
    setupTimer();
    createFood();
}

void MainWindow::createSnake() {
    createHead();
    createBody();
}

void MainWindow::createHead() {
    Snake *snakeHead = new Snake(BodyType::HEAD);
    scene->addItem(snakeHead);
    snakeHead->setPos(200, 200); 
    snake.append(snakeHead);
}

void MainWindow::createBody() {
    for (size_t i = 1; i < 4; i++)
    {
        Snake *snakeBody = new Snake(BodyType::BODY);
        scene->addItem(snakeBody);
        snakeBody->setPos(200 - i * 10, 200);
        snake.append(snakeBody);
    }
}

void MainWindow::setupTimer() {
    connect(&timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer.start(100); // Game loop every 100 ms
}

void MainWindow::gameLoop() {
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
        updateScoreDisplay();

        do
        {
            food->generateNewPosition();
        } while (checkFoodCollision());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
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
            QMainWindow::keyPressEvent(event);
            return;
    }
    snake.first()->changeDirection(newDirection);
}

void MainWindow::createFood() {
    food = new Food(470, 470);

    while (checkFoodCollision()) {
        food->generateNewPosition();
    }
    scene->addItem(food);
}

bool MainWindow::checkFoodCollision() {
    for (auto segment : snake) {
        if (segment->pos().x() == food->pos().x() && segment->pos().y() == food->pos().y()) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

void MainWindow::updateScoreDisplay() {
    ui->scoreLabel->setText("Score: " + QString::number(score));
}
