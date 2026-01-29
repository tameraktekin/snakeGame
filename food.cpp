#include "food.h"

Food::Food(int maxWidth, int maxHeight, QGraphicsItem *parent) : maxWidth(maxWidth), maxHeight(maxHeight), QGraphicsRectItem(parent) {
    generateNewPosition();
    setRect(0, 0, 10, 10);
}

void Food::generateNewPosition() {
    int x = QRandomGenerator::global()->bounded(maxWidth / 10) * 10;
    int y = QRandomGenerator::global()->bounded(maxHeight / 10) * 10;
    setPos(x, y);
}

void Food::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect());
}