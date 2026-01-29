#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "constants.h"

// Direction enumeration
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Body Type enumeration
enum class BodyType {
    HEAD,
    BODY
};

// Snake class
class Snake : public QGraphicsRectItem {
public:
    Snake(BodyType type, QGraphicsItem *parent = nullptr);

    QPointF move(const QPointF& previousPosition);
    void changeDirection(Direction newDirection);
    Snake* grow();
    bool checkCollision(QList<QGraphicsItem *> &items) const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Direction currentDirection;
    BodyType m_type;
    void drawHead(QPainter *painter);
    void drawBody(QPainter *painter);
};

#endif // SNAKE_H