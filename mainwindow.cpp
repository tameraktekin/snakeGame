#include "mainwindow.h"
#include "./ui_mainwindow.h" // Created automatically by CMake/UIC

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    setupScene();
    setupGame();
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
}

void MainWindow::createSnake() {
    createHead();
    createBody();
}

void MainWindow::createHead() {
    Snake *snakeHead = new Snake(BodyType::HEAD);
    scene->addItem(snakeHead);
    snakeHead->setPos(225, 225); // Center the snake head
    snake.append(snakeHead);
}

void MainWindow::createBody() {
    for (size_t i = 1; i < 4; i++)
    {
        Snake *snakeHead = new Snake(BodyType::BODY);
        scene->addItem(snakeHead);
        snakeHead->setPos(225 - i * 10, 225); // Center the snake head
        snake.append(snakeHead);
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
        previousPosition = segment->move(previousPosition);
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