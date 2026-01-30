#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "constants.h"

/**
 * @brief Direction enumeration for snake movement.
 */
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @brief BodyType enumeration to distinguish between head and body segments.
 */
enum class BodyType {
    HEAD,
    BODY
};

/**
 * @class Snake
 * @brief Represents a single segment of the snake (Head or Body).
 * * Inherits from QGraphicsRectItem. Handles its own movement logic 
 * and collision detection with other scene items.
 */

class Snake : public QGraphicsRectItem {
public:
    /**
     * @brief Constructor for Snake segment.
     * @param type The type of the snake segment (HEAD or BODY).
     * @param parent The parent QGraphicsItem.
     */
    Snake(BodyType type, QGraphicsItem *parent = nullptr);

    /**
     * @brief Moves the snake segment based on its current direction.
     * It moves the segment to the position of the previous segment
     * and returns that previous position.
     * Movement occurs in a snake-like fashion.
     * @param previousPosition The position of the previous segment.
     * @return The previous position before movement.
     */
    QPointF move(const QPointF& previousPosition);

    /**
     * @brief Changes the current direction of the snake segment.
     * @param newDirection The new direction to set.
     */
    void changeDirection(Direction newDirection);

    /**
     * @brief Grows the snake by adding a new body segment.
     * @return A pointer to the newly created Snake body segment.
     */
    Snake* grow();

    /**
     * @brief Checks for collision with body parts in the scene.
     * @param items List of QGraphicsItems to check for collision.
     * @return True if a collision with a body part is detected, false otherwise.
     */
    bool checkCollision(QList<QGraphicsItem *> &items) const;

    /**
     * @brief Gets the current direction of the snake segment.
     * @return The current direction.
     */
    Direction getDirection() const { return currentDirection; }

    /**
     * @brief Gets the body type of the snake segment.
     * @return The body type (HEAD or BODY).
     */
    BodyType getBodyType() const { return m_type; }

protected:
    /**
     * @brief Paints the snake segment.
     * @param painter The QPainter object.
     * @param option Style options for the graphics item.
     * @param widget The widget being painted on.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    /**
     * @brief Current movement direction of the snake segment.
     */
    Direction currentDirection;

    /**
     * @brief Type of the snake segment (HEAD or BODY).
     */
    BodyType m_type;

    /**
     * @brief Draws the head of the snake.
     * @param painter The QPainter object.
     */
    void drawHead(QPainter *painter);

    /**
     * @brief Draws the body of the snake.
     * @param painter The QPainter object.
     */
    void drawBody(QPainter *painter);
};

#endif // SNAKE_H