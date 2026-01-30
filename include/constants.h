#pragma once
#include <QColor>

/**
 * @file constants.h
 * @brief Global configuration and magic numbers for the Snake game.
 * * Centralizes all gameplay tuning parameters like speed, grid dimensions, 
 * and scoring logic to ensure consistency across the engine.
 */

/**
 * @namespace Constants
 * @brief Contains all constant values used throughout the Snake game.
 * Includes settings for tile size, movement distance, scoring,
 * and nested namespaces for speed, grid dimensions, snake properties, food properties, and audio resources.
 * This organization helps maintain clarity and ease of access to game configuration values.
 */
namespace Constants {
    const int TILE_SIZE = 9;
    const int MOVE_DISTANCE = 10;
    const int SCORE_PER_FOOD = 10;

    /**
     * @namespace Speed
     * @brief Constants related to game speed and scoring milestones.
     * Controls how the game speed increases as the player scores points.
     * Includes initial speed, speed increments, and scoring milestones.
     */
    namespace Speed {
        const int INITIAL_SPEED = 100; // in milliseconds
        const int SPEED_INCREMENT = 10; // in milliseconds
        const int MIN_SPEED = 20; // in milliseconds
        const int SCORE_INIT_MILESTONE = 100; // in points
        const int SCORE_MILESTONE_MULTIPLIER = 10; // in points
    }

    /**
     * @namespace Grid
     * @brief Constants defining the dimensions of the game grid.
     * Specifies the width and height of the playable area.
     * These values ensure the game elements fit within the designated space.
     */
    namespace Grid {
        const int WIDTH = 470; // in pixels
        const int HEIGHT = 470; // in pixels
    }

    /**
     * @namespace Snake
     * @brief Constants related to the snake's properties.
     * Defines the snake's color, head and body rounding, initial length, and starting position.
     * These settings help establish the snake's appearance and initial state in the game.
     */
    namespace Snake {
        const QColor COLOR = Qt::green;
        const int HEAD_ROUNDING = 4;
        const int BODY_ROUNDING = 2;
        const int INITIAL_SNAKE_LENGTH = 4;
        const int INITIAL_SNAKE_POS = 200;
    }

    /**
     * @namespace Food
     * @brief Constants related to the food properties.
     * Defines the food's color and size.
     * These settings help establish the food's appearance in the game.
     */
    namespace Food {
        const QColor COLOR = Qt::yellow;
        const int SIZE = 10;
    }

    /**
     * @namespace Audio
     * @brief Constants for audio resource paths.
     * Specifies the file paths for sound effects used in the game.
     * This organization helps manage audio assets efficiently.
     */
    namespace Audio {
        const QString SOUND_EFFECT_EAT = ":/assets/sounds/eat.wav";
        const QString SOUND_EFFECT_GAME_OVER = ":/assets/sounds/gameOver.wav";
    }
}