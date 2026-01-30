#ifndef FOOD_H
#define FOOD_H

#include <utility> 
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QRandomGenerator>
#include "constants.h"

/**
 * @class Food
 * @brief Represents the consumable item that appears on the grid.
 * * Responsible for generating random positions that are perfectly 
 * aligned with the TILE_SIZE grid.
 */

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