#include "Toolbox.h"
#include "Minesweeper.h"

using namespace sf;

Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance; // returns the instance of the toolbox making sure that there is only one instance of toolbox and it acts like a singleton
}

Toolbox::Toolbox() { // Toolbox constructor
    window.create(VideoMode(800, 600), "P4 - Minesweeper, <Alejandro Mateus>"); // main window
    gameState = new GameState(sf::Vector2i (25, 16), 50); // main gamestate
    debugButton = new Button(sf::Vector2f (window.getSize().x/(2.0) + 96, 512), toggleDebugMode); // creates a debug button
    newGameButton = new Button(sf::Vector2f ((window.getSize().x / 2.0) - 32, 512), launch); // creates a new game button
    testButton1 = new Button(sf::Vector2f (window.getSize().x/(2.0) + 160, 512), restart); // creates a teat one button
    testButton2 = new Button(sf::Vector2f (window.getSize().x/(2.0) + 224, 512), restart); // creates a test two button
    testButton3 = new Button(sf::Vector2f (window.getSize().x/2.0 + 288, 512), restart); // creates a test three button

    // Sets sprite texture and position for the debug button
    Texture debugTexture;
    debugTexture.loadFromFile("../images/debug.png");
    Sprite debugSprite(debugTexture);
    debugButton->setSprite(&debugSprite);

    // Sets sprite texture and position for the new game button
    Texture newGameTexture;
    newGameTexture.loadFromFile("../images/face_happy.png");
    Sprite newGameSprite(newGameTexture);
    newGameButton->setSprite(&newGameSprite);

    // Sets sprite texture and position for the test 1 button
    Texture test1Texture;
    test1Texture.loadFromFile("../images/test_1.png");
    Sprite test1Sprite(test1Texture);
    testButton1->setSprite(&test1Sprite);

    // Sets sprite texture and position for the test 2 button
    Texture test2Texture;
    test2Texture.loadFromFile("../images/test_2.png");
    Sprite test2Sprite(test2Texture);
    testButton2->setSprite(&test2Sprite);

    // Sets sprite texture and position for the test 3 button
    Texture test3Texture;
    test3Texture.loadFromFile("../images/test_3.png");
    Sprite test3Sprite(test3Texture);
    testButton3->setSprite(&test3Sprite);

}

Vector2i Toolbox::_dimentions() {
    Vector2i currentSize(25, 16); // change this to get different sizes of the board
    return currentSize;
}
