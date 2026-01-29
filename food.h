#ifndef FOOD_H
#define FOOD_H

#include <utility> 
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QRandomGenerator>

class Food : public QGraphicsRectItem {
public:
    Food(int maxWidth, int maxHeight, QGraphicsItem *parent = nullptr);

    // Generates a new position for the food
    void generateNewPosition();
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; 

private:
    int maxWidth;
    int maxHeight;
};

#endif // FOOD_H