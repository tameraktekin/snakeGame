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
    /**
     * @brief Constructor for the Food class.
     * @param maxWidth Maximum width of the game area.
     * @param maxHeight Maximum height of the game area.
     * @param parent Optional parent QGraphicsItem.
     */
    Food(int maxWidth, int maxHeight, QGraphicsItem *parent = nullptr);

    /**
     * @brief Generates a new random position for the food item.
     * * Ensures the position is in the scene.
     */
    void generateNewPosition();

    /**
     * @brief Paints the food item.
     * @param painter QPainter object used for drawing.
     * @param option Style options for the graphics item.
     * @param widget Optional widget parameter.
     */
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; 

private:
    /**
     * @brief Maximum width for positioning the food item.
     */
    int maxWidth;

    /**
     * @brief Maximum height for positioning the food item.
     */
    int maxHeight;
};

#endif // FOOD_H