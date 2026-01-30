#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <QMessageBox>
#include "snake.h"
#include "food.h"
#include "constants.h"
#include "audiomanager.h"


/**
 * @class GameManager
 * @brief The brain of the Snake game.
 * * Coordinates the interaction between the Snake, Food, and AudioManager.
 * It manages the game loop timer and handles score progression.
 */

class GameManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the GameManager with the provided QGraphicsScene.
     * @param scene Pointer to the QGraphicsScene where the game elements are rendered.
     */
    GameManager(QGraphicsScene* scene);

    /**
     * @brief Destructor to clean up resources.
     */
    ~GameManager();

    /**
     * @brief Handles key press events to change the snake's direction.
     * @param event Pointer to the QKeyEvent containing key press information.
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief Retrieves the current length of the snake.
     * @return The length of the snake as an integer.
     */
    int getSnakeLength() const { return snake.size(); }

    /**
     * @brief Retrieves the current score.
     * @return The current score as an integer.
     */
    int getScore() const { return score; }

    /**
     * @brief Retrieves the current position of the snake's head.
     * @return The position of the snake's head as a QPointF.
     */
    QPointF getSnakePosition() const { return snake.first()->pos(); }

signals:
    /**
     * @brief Signal emitted when the score changes.
     * @param newScore The updated score.
     */
    void scoreChanged(int newScore);

    /**
     * @brief Signal emitted when the game is over.
     * @param finalScore The final score at game over.
     */
    void gameOver(int finalScore);

private slots:
    /**
     * @brief The main game loop, called periodically by the timer.
     */
    void gameLoop();

private:
    /**
     * @brief Pointer to the QGraphicsScene where the game is rendered.
     */
    QGraphicsScene* scene;

    /**
     * @brief List of pointers to Snake segments (head and body).
     */
    QList<Snake*> snake;

    /**
     * @brief Pointer to the Food item in the game.
     */
    Food* food;

    /**
     * @brief Timer to control the game loop speed.
     */
    QTimer timer;

    /**
     * @brief Current score of the game.
     */
    int score;

    /**
     * @brief Milestone score for speed increase.
     */
    int scoreMilestone;

    /**
     * @brief Pointer to the AudioManager for sound effects.
     */
    AudioManager* audioManager;

    /**
     * @brief Sets up the initial game state.
     */
    void setupGame();

    /**
     * @brief Configures the game loop timer.
     */
    void setupTimer();

    /**
     * @brief Configures speed handling based on score.
     */
    void setupSpeedHandling();

    /**
     * @brief Initializes the AudioManager and loads sound effects.
     */
    void setupAudioManager();

    /**
     * @brief Creates the initial snake with head and body segments.
     */
    void createSnake();

    /**
     * @brief Creates the snake's head segment.
     */
    void createHead();

    /**
     * @brief Creates the snake's body segments.
     */
    void createBody();

    /**
     * @brief Creates the food item at a random position.
     */
    void createFood();

    /**
     * @brief Checks for collision between the snake's head and the food.
     */
    bool checkFoodCollision();

    /**
     * @brief Checks if the score has reached the milestone for speed increase.
     */
    bool checkScoreMilestone();

    /**
     * @brief Handles the logic for increasing the game speed.
     */
    void handleSpeedIncrease();
};

#endif // GAMEMANAGER_H