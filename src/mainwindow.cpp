#include "mainwindow.h"
#include "./ui_mainwindow.h" // Created automatically by CMake/UIC

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    setupScene();
    setupGameManager();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupScene() {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 
                        Constants::Grid::WIDTH, Constants::Grid::HEIGHT); // Set scene size

    ui->gameView->setScene(scene);
    ui->gameView->setRenderHint(QPainter::Antialiasing);
    ui->gameView->setFocusPolicy(Qt::StrongFocus);
    ui->gameView->setFocus();
}

void MainWindow::setupGameManager() {
    gameManager = new GameManager(scene);
    connect(gameManager, &GameManager::scoreChanged, this, &MainWindow::updateScoreDisplay);
    connect(gameManager, &GameManager::gameOver, this, &MainWindow::handleGameOver);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    gameManager->keyPressed(event);
}

void MainWindow::updateScoreDisplay(int score) {
    ui->scoreLabel->setText("Score: " + QString::number(score));
}

void MainWindow::handleGameOver(int finalScore) {
    QMessageBox* gameOverBox = createGameOverBox(finalScore);
    int ret = gameOverBox->exec();

    switch (ret) {
        case QMessageBox::Yes:
            resetGame();
            break;
        case QMessageBox::No:
            close();
            break;
        default:
            break;
    }
}

QMessageBox* MainWindow::createGameOverBox(int finalScore) {
    QMessageBox* gameOverBox = new QMessageBox(this);
    gameOverBox->setText("Game Over! Your final score is " + QString::number(finalScore) + ".");
    gameOverBox->setWindowTitle("Game Over");
    gameOverBox->setIcon(QMessageBox::Warning);
    gameOverBox->setInformativeText("Do you want to restart the game?");
    gameOverBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    gameOverBox->setDefaultButton(QMessageBox::Yes);
    return gameOverBox;
}

void MainWindow::resetGame() {
    delete scene;
    setupScene();

    delete gameManager;
    setupGameManager();

    ui->scoreLabel->setText("Score: 0");
}