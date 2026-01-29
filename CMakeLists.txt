cmake_minimum_required(VERSION 3.16)
project(snakeGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON) # Automatically processes .ui files
set(CMAKE_AUTOMOC ON) # Automatically processes Q_OBJECT macros
set(CMAKE_AUTORCC ON) # Automatically processes .qrc files

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(snakeGame
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    snake.cpp
    snake.h
    food.cpp
    food.h
)

target_link_libraries(snakeGame PRIVATE Qt6::Widgets)