cmake_minimum_required(VERSION 3.16)
project(snakeGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/forms")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON) # Automatically processes .ui files
set(CMAKE_AUTOMOC ON) # Automatically processes Q_OBJECT macros
set(CMAKE_AUTORCC ON) # Automatically processes .qrc files
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gamemanager.cpp
    src/snake.cpp
    src/food.cpp
    src/audiomanager.cpp
)

# Add header files
set(HEADERS
    include/mainwindow.h
    include/gamemanager.h
    include/snake.h
    include/food.h
    include/constants.h
    include/audiomanager.h
)

# Add .qrc to the sources
set(RESOURCES resources.qrc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_source_files_properties(${RESOURCES} PROPERTIES SKIP_AUTOGEN OFF)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Multimedia)
