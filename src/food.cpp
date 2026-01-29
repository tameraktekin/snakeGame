#include "food.h"

Food::Food(int maxWidth, int maxHeight, QGraphicsItem *parent) : maxWidth(maxWidth), maxHeight(maxHeight), QGraphicsRectItem(parent) {
    generateNewPosition();
    setRect(0, 0, Constants::Food::SIZE, Constants::Food::SIZE);
}

void Food::generateNewPosition() {
    int x = QRandomGenerator::global()->bounded(maxWidth / Constants::Food::SIZE) 
            * Constants::Food::SIZE;

    int y = QRandomGenerator::global()->bounded(maxHeight / Constants::Food::SIZE) 
            * Constants::Food::SIZE;
    setPos(x, y);
}

void Food::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Constants::Food::COLOR);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect());
}