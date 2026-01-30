#include <QtTest>
#include <QSignalSpy>
#include "../include/snake.h"
#include "../include/food.h"
#include "../include/gamemanager.h"

class SnakeTest : public QObject {
    Q_OBJECT

private slots:
    void testMovementRight();
    void testMovementLeft();
    void testMovementUp();
    void testMovementDown();
    void testPreventIllegalUturn();
    void testGrow();
    void testFoodGeneration();

    void testInitGame();
    void testKeyPressHandling();
    void testEatingFoodSignal();
    void testSpeedMilestoneHandling();
    void testGameOverSignal();

    void testAudioManagerIntegration();
};

void SnakeTest::testMovementRight() {
    Snake snake(BodyType::HEAD);
        
    snake.changeDirection(Direction::RIGHT);
    QCOMPARE(snake.getDirection(), Direction::RIGHT);

    snake.move(snake.pos()); // Move one step
    // Assert that the head moved by the tile size (e.g., 10 pixels)
    QCOMPARE(snake.pos().x(), Constants::MOVE_DISTANCE);
}

void SnakeTest::testMovementLeft() {
    Snake snake(BodyType::HEAD);
        
    snake.changeDirection(Direction::UP); // First move up to avoid reverse direction
    snake.changeDirection(Direction::LEFT);
    QCOMPARE(snake.getDirection(), Direction::LEFT);

    snake.move(snake.pos()); // Move one step
    // Assert that the head moved by the tile size (e.g., 10 pixels)
    QCOMPARE(snake.pos().x(), Constants::Grid::WIDTH - Constants::MOVE_DISTANCE);
}

void SnakeTest::testMovementUp() {
    Snake snake(BodyType::HEAD);
        
    snake.changeDirection(Direction::UP);
    QCOMPARE(snake.getDirection(), Direction::UP);

    snake.move(snake.pos()); // Move one step
    // Assert that the head moved by the tile size (e.g., 10 pixels)
    QCOMPARE(snake.pos().y(), Constants::Grid::HEIGHT - Constants::MOVE_DISTANCE);
}

void SnakeTest::testMovementDown() {
    Snake snake(BodyType::HEAD);
        
    snake.changeDirection(Direction::DOWN);
    QCOMPARE(snake.getDirection(), Direction::DOWN);

    snake.move(snake.pos()); // Move one step
    // Assert that the head moved by the tile size (e.g., 10 pixels)
    QCOMPARE(snake.pos().y(), Constants::MOVE_DISTANCE);
}

void SnakeTest::testPreventIllegalUturn() {
    Snake snake(BodyType::HEAD); // Starts RIGHT
    snake.changeDirection(Direction::LEFT); 
    
    // It should STILL be RIGHT because LEFT was ignored
    QCOMPARE(snake.getDirection(), Direction::RIGHT); 
}

void SnakeTest::testGrow() {
    Snake snake(BodyType::HEAD);
    Snake* newBodyPart = snake.grow();
    QVERIFY(newBodyPart != nullptr);
    QCOMPARE(newBodyPart->getBodyType(), BodyType::BODY);
    QCOMPARE(newBodyPart->pos().x(), snake.pos().x());
    QCOMPARE(newBodyPart->pos().y(), snake.pos().y());

}

void SnakeTest::testFoodGeneration() {
    Food food(Constants::Grid::WIDTH, Constants::Grid::HEIGHT);

    // Run 100 times to ensure randomness doesn't break boundaries
    for (int i = 0; i < 100; ++i) {
        food.generateNewPosition();
        
        QPointF pos = food.pos();
        
        // 1. Check Horizontal Boundary
        QVERIFY(pos.x() >= 0);
        QVERIFY(pos.x() < Constants::Grid::WIDTH);
        
        // 2. Check Vertical Boundary
        QVERIFY(pos.y() >= 0);
        QVERIFY(pos.y() < Constants::Grid::HEIGHT);
        
        // 3. Check Alignment (Is it on the grid?)
        // The x and y should always be multiples of Food::SIZE
        int xInt = static_cast<int>(pos.x());
        int yInt = static_cast<int>(pos.y());
        
        QCOMPARE(xInt % Constants::Food::SIZE, 0);
        QCOMPARE(yInt % Constants::Food::SIZE, 0);
    }
}

void SnakeTest::testInitGame() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);

    // Check that the snake has been initialized with the correct length
    QCOMPARE(gameManager.getSnakeLength(), Constants::Snake::INITIAL_SNAKE_LENGTH);

    // Check that the food has been created. There should be one food item in the scene.
    QCOMPARE(scene.items().size(), Constants::Snake::INITIAL_SNAKE_LENGTH + 1); 

    // Check that the initial score is zero
    QCOMPARE(gameManager.getScore(), 0);

    // Check that the snake's head is at the initial position
    QPointF headPos = gameManager.getSnakePosition();
    QCOMPARE(headPos.x(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS));
    QCOMPARE(headPos.y(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS));
}

void SnakeTest::testKeyPressHandling() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);

    QKeyEvent rightKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
    gameManager.keyPressed(&rightKeyEvent);
    // Wait: Let the real timer fire gameLoop()
    // We wait slightly longer than INITIAL_SPEED to ensure the tick happens
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);
    QCOMPARE(gameManager.getSnakePosition().x(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS + Constants::MOVE_DISTANCE));

    QKeyEvent upKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
    gameManager.keyPressed(&upKeyEvent);
    // Wait: Let the real timer fire gameLoop()
    // We wait slightly longer than INITIAL_SPEED to ensure the tick happens
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);
    QCOMPARE(gameManager.getSnakePosition().y(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS - Constants::MOVE_DISTANCE));

    QKeyEvent leftKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
    gameManager.keyPressed(&leftKeyEvent);
    // Wait: Let the real timer fire gameLoop()
    // We wait slightly longer than INITIAL_SPEED to ensure the tick happens
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);
    // Since the last direction was UP, LEFT is valid
    QCOMPARE(gameManager.getSnakePosition().x(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS + Constants::MOVE_DISTANCE - Constants::MOVE_DISTANCE));

    QKeyEvent downKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
    gameManager.keyPressed(&downKeyEvent);
    // Wait: Let the real timer fire gameLoop()
    // We wait slightly longer than INITIAL_SPEED to ensure the tick happens
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);
    // Since the last direction was LEFT, DOWN is valid
    QCOMPARE(gameManager.getSnakePosition().y(), static_cast<qreal>(Constants::Snake::INITIAL_SNAKE_POS - Constants::MOVE_DISTANCE + Constants::MOVE_DISTANCE));
}

void SnakeTest::testEatingFoodSignal() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);
    
    // Setup Spy
    QSignalSpy scoreSpy(&gameManager, &GameManager::scoreChanged);

    // Find Food
    QList<QGraphicsItem*> items = scene.items();
    Food* targetFood = nullptr;

    for (auto item : items) {
        if (Food* f = dynamic_cast<Food*>(item)) targetFood = f;
    }
    // Align Snake and Food
    QPointF foodPos = gameManager.getSnakePosition();
    foodPos.setX(foodPos.x() + Constants::MOVE_DISTANCE); // Place food right in front of head position
    targetFood->setPos(foodPos);      

    // Wait for the game timer to tick once
    // This allows the private gameLoop() to run naturally
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);

    // Verify Results via Signals
    QCOMPARE(scoreSpy.count(), 1); 
    QCOMPARE(scoreSpy.at(0).at(0).toInt(), 10);
    
    // Verify physical growth
    QCOMPARE(gameManager.getSnakeLength(), Constants::Snake::INITIAL_SNAKE_LENGTH + 1);
}

void SnakeTest::testSpeedMilestoneHandling() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);
    QTimer* timer = gameManager.findChild<QTimer*>();

    for (size_t i = 0; i < Constants::Speed::SCORE_INIT_MILESTONE / Constants::SCORE_PER_FOOD; i++) {
        // Find Food
        QList<QGraphicsItem*> items = scene.items();
        Food* targetFood = nullptr;

        for (auto item : items) {
            if (Food* f = dynamic_cast<Food*>(item)) targetFood = f;
        }
        
        // Align Snake and Food
        QPointF foodPos = gameManager.getSnakePosition();
        foodPos.setX(foodPos.x() + Constants::MOVE_DISTANCE); // Place food right in front of head position
        targetFood->setPos(foodPos);      

        // Wait for the game timer to tick once
        QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);
    }
    // After eating enough food to reach the first milestone, the timer interval should have decreased
    int newSpeed = timer->interval();
    QCOMPARE(newSpeed, Constants::Speed::INITIAL_SPEED - Constants::Speed::SPEED_INCREMENT);
}

void SnakeTest::testGameOverSignal() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);
    
    // Setup Spy
    QSignalSpy gameOverSpy(&gameManager, &GameManager::gameOver);

    // Force Collision by placing head on its own body
    QList<QGraphicsItem*> items = scene.items();
    Snake* head = nullptr;
    Snake* bodyPart = nullptr;

    for (auto item : items) {
        if (Snake* s = dynamic_cast<Snake*>(item)) {
            if (s->getBodyType() == BodyType::HEAD) head = s;
            else if (s->getBodyType() == BodyType::BODY && bodyPart == nullptr) bodyPart = s; // Get first body part
        }
    }

    // Place head on top of the first body part to simulate collision
    head->setPos(bodyPart->pos());

    // Wait for the game timer to tick once
    QTest::qWait(Constants::Speed::INITIAL_SPEED + 20);

    // Verify Game Over Signal Emitted
    QCOMPARE(gameOverSpy.count(), 1); 
    QCOMPARE(gameOverSpy.at(0).at(0).toInt(), 0); // Final score should be 0 as no food was eaten
}

void SnakeTest::testAudioManagerIntegration() {
    QGraphicsScene scene;
    GameManager gameManager(&scene);
    
    // 1. Find the AudioManager (which is a child of gameManager)
    AudioManager* audio = gameManager.findChild<AudioManager*>();
    QVERIFY(audio != nullptr);

    // 2. Find the Sound Effects inside the AudioManager
    // We look for all QSoundEffect children
    QList<QSoundEffect*> sounds = audio->findChildren<QSoundEffect*>();
    QVERIFY(!sounds.isEmpty());

    // 3. Trigger an "Eat" event via Signal
    // Instead of moving the snake, we can just emit the signal directly!
    QSignalSpy spy(&gameManager, &GameManager::scoreChanged);
    emit gameManager.scoreChanged(10);

    // 4. Verification
    // Even if we can't catch the sound playing (it's too fast), 
    // we can verify the files loaded correctly.
    for (QSoundEffect* sound : sounds) {
        QVERIFY2(sound->status() != QSoundEffect::Error, 
                 "Sound file failed to load! Check your .qrc paths.");
    }
}

QTEST_MAIN(SnakeTest)
#include "testmain.moc"