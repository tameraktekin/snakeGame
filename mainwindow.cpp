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
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    gameManager->keyPressed(event);
}
void MainWindow::updateScoreDisplay(int score) {
    ui->scoreLabel->setText("Score: " + QString::number(score));
}
