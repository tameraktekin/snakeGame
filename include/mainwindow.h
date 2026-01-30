#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class manages the main window of the game application.
 * It handles user input, updates the game state, and displays the game scene.
 * It also manages the game over scenario and score display.
 * @see GameManager for game logic management.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow object.
     * @param parent The parent widget, default is nullptr.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

private:
    /**
     * @brief UI pointer for the main window.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Graphics view to display the game scene.
     */
    QGraphicsScene *scene;

    /**
     * @brief GameManager instance to handle game logic.
     */
    GameManager *gameManager;

    /**
     * @brief Sets up the game scene.
     */
    void setupScene();

    /**
     * @brief Sets up the GameManager.
     */
    void setupGameManager();

    /**
     * @brief Updates the score display on the UI.
     * @param score The current score to display.
     */
    void updateScoreDisplay(int score);

    /**
     * @brief Handles key press events for user input.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Handles the game over scenario.
     * @param finalScore The final score achieved by the player.
     */
    void handleGameOver(int finalScore);

    /**
     * @brief Creates a message box to display the game over message and final score.
     * @param finalScore The final score achieved by the player.
     * @return A pointer to the created QMessageBox.
     */
    QMessageBox* createGameOverBox(int finalScore);

    /**
     * @brief Resets the game to its initial state.
     */
    void resetGame();
};
#endif