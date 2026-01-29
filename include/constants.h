#pragma once
#include <QColor>


namespace Constants {
    const int TILE_SIZE = 9;
    const int MOVE_DISTANCE = 10;

    namespace Speed {
        const int INITIAL_SPEED = 100; // in milliseconds
        const int SPEED_INCREMENT = 10; // in milliseconds
        const int MIN_SPEED = 20; // in milliseconds
        const int SCORE_INIT_MILESTONE = 100; // in points
        const int SCORE_MILESTONE_MULTIPLIER = 10; // in points
    }

    namespace Grid {
        const int WIDTH = 470;
        const int HEIGHT = 470;
    }

    namespace Snake {
        const QColor COLOR = Qt::green;
        const int HEAD_ROUNDING = 4;
        const int BODY_ROUNDING = 2;
        const int INITIAL_SNAKE_LENGTH = 4;
        const int INITIAL_SNAKE_POS = 200;
    }

    namespace Food {
        const QColor COLOR = Qt::yellow;
        const int SIZE = 10;
    }
}