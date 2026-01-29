#include "snake.h"

Snake::Snake(BodyType type, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    setRect(0, 0, 9, 9);
    m_type = type;
    currentDirection = Direction::RIGHT;
}

void Snake::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    
    switch (m_type) {
        case BodyType::HEAD:
            drawHead(painter);
            break;
        case BodyType::BODY:
            drawBody(painter);
            break;
        default:
            break;
    }
}

void Snake::drawHead(QPainter *painter) {
    painter->setBrush(Qt::green);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(rect(), 4, 4);
}

void Snake::drawBody(QPainter *painter) {
    painter->setBrush(Qt::green);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(rect(), 2, 2);
}

QPointF Snake::move(const QPointF& previousPosition) {
    QPointF currentPosition = pos();
    if (m_type == BodyType::HEAD) {
        switch (currentDirection){
        case Direction::UP:
            setPos(x(), static_cast<qreal>((static_cast<int>(y()) - 10 + 470) % 470)); // Move up by 10 units
            break;
        case Direction::DOWN:
            setPos(x(), static_cast<qreal>((static_cast<int>(y()) + 10) % 470)); // Move down by 10 units
            break;
        case Direction::LEFT:
            setPos(static_cast<qreal>((static_cast<int>(x()) - 10 + 470) % 470), y()); // Move left by 10 units
            break;
        case Direction::RIGHT:
            setPos(static_cast<qreal>((static_cast<int>(x()) + 10) % 470), y()); // Move right by 10 units
            break;

        default:
            break;
        }
    }
    else {
        setPos(previousPosition);
    }
    return currentPosition;
}

void Snake::changeDirection(Direction newDirection) {
    // Prevent reversing direction
    if (currentDirection == Direction::UP && newDirection == Direction::DOWN) {
        return;
    }
    if (currentDirection == Direction::DOWN && newDirection == Direction::UP) {
        return;
    }
    if (currentDirection == Direction::LEFT && newDirection == Direction::RIGHT) {
        return;
    }
    if (currentDirection == Direction::RIGHT && newDirection == Direction::LEFT) {
        return;
    }
    
    currentDirection = newDirection;
}

bool Snake::checkCollision(QList<QGraphicsItem *> &items) const{
    // Check for collision with body parts
    for (auto item : items) {
        Snake* part = dynamic_cast<Snake*>(item);
        if (part && part->m_type == BodyType::BODY) {
            return true; // Collision detected
        }
    }
    return false;
}

Snake* Snake::grow() {
    Snake* newBodyPart = new Snake(BodyType::BODY);
    newBodyPart->setPos(this->pos());
    return newBodyPart;
}