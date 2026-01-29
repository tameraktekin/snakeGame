#include "snake.h"

Snake::Snake(BodyType type, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    setRect(0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE);
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
    painter->setBrush(Constants::Snake::COLOR);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(rect(), 
                             Constants::Snake::HEAD_ROUNDING,
                             Constants::Snake::HEAD_ROUNDING);
}

void Snake::drawBody(QPainter *painter) {
    painter->setBrush(Constants::Snake::COLOR);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(rect(), 
                             Constants::Snake::BODY_ROUNDING,
                             Constants::Snake::BODY_ROUNDING);
}

QPointF Snake::move(const QPointF& previousPosition) {
    QPointF currentPosition = pos();
    if (m_type == BodyType::HEAD) {
        switch (currentDirection){
            case Direction::UP:
                setPos(x(), 
                    static_cast<qreal>((static_cast<int>(y()) - Constants::MOVE_DISTANCE + 
                    Constants::Grid::HEIGHT) % Constants::Grid::HEIGHT)); // Move up by MOVE_DISTANCE units
                break;

            case Direction::DOWN:
                setPos(x(), 
                    static_cast<qreal>((static_cast<int>(y()) + Constants::MOVE_DISTANCE) % 
                    Constants::Grid::HEIGHT)); // Move down by MOVE_DISTANCE units
                break;

            case Direction::LEFT:
                setPos(static_cast<qreal>((static_cast<int>(x()) - Constants::MOVE_DISTANCE + 
                    Constants::Grid::WIDTH) % Constants::Grid::WIDTH), y()); // Move left by MOVE_DISTANCE units
                break;

            case Direction::RIGHT:
                setPos(static_cast<qreal>((static_cast<int>(x()) + Constants::MOVE_DISTANCE) % 
                    Constants::Grid::WIDTH), y()); // Move right by MOVE_DISTANCE units
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