#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "snake.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gameLoop();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<Snake*> snake;
    QTimer timer;

    void keyPressEvent(QKeyEvent *event) override;

    void setupScene();
    void setupGame();
    void setupTimer();
    void createSnake();
    void createHead();
    void createBody();
};
#endif