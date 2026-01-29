#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    GameManager *gameManager;

    void setupScene();
    void setupGameManager();
    void updateScoreDisplay(int score);
    void keyPressEvent(QKeyEvent *event) override;
    void handleGameOver(int finalScore);
    QMessageBox* createGameOverBox(int finalScore);
    void resetGame();
};
#endif