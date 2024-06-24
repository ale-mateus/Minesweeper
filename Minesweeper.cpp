#include <iostream>
#include "Minesweeper.h"
#include "GameState.h"
#include "Toolbox.h"

static bool debugMode = false;

int launch() { // starts a new random game
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState = new GameState(); // Creates a new gamestate using the default constructor (random)
    render(); // calls the method that renders everything to the toolbox window
    return 0;
}

void restart() { // makes a new games state that is dependent on the file
    if(getDebugMode() == true){ // makes sure that the debug mode is toggled off when switching between files modes
        toggleDebugMode();
    }
    Toolbox& toolbox = Toolbox::getInstance();
    if(toolbox.gameState->getPlayStatus() == GameState::WIN){
        toolbox.gameState = new GameState("../boards/testboard1.brd");
    }else if(toolbox.gameState->getPlayStatus() == GameState::LOSS){
        toolbox.gameState = new GameState("../boards/testboard2.brd");
    }else if(toolbox.gameState->getPlayStatus() == GameState::PLAYING){
        toolbox.gameState = new GameState("../boards/testboard3.brd");
    }
    render(); // calls the method that renders everything to the toolbox window
}

void render() { // Draw UI elements based on the current game state and debug mode
    Toolbox& toolbox = Toolbox::getInstance(); // gets the singleton toolbox

    int sizeX = toolbox._dimentions().x;
    int sizeY = toolbox._dimentions().y;

    Texture newGameTexture; // Makes the sprite for the happy face/ restart button
    newGameTexture.loadFromFile("../images/face_happy.png");
    Sprite newGameSprite(newGameTexture);
    newGameSprite.setPosition(toolbox.newGameButton->getPosition());

    Texture debugTexture; // Makes the sprite for the debug button
    debugTexture.loadFromFile("../images/debug.png");
    Sprite debugSprite;
    debugSprite.setTexture(debugTexture);
    debugSprite.setPosition(toolbox.debugButton->getPosition());

    Texture test1Texture; // Makes the sprite for the test case 1 button
    test1Texture.loadFromFile("../images/test_1.png");
    Sprite test1Sprite;
    test1Sprite.setTexture(test1Texture);
    test1Sprite.setPosition(toolbox.testButton1->getPosition());

    Texture test2Texture; // Makes the sprite for the test case 2 button
    test2Texture.loadFromFile("../images/test_2.png");
    Sprite test2Sprite;
    test2Sprite.setTexture(test2Texture);
    test2Sprite.setPosition(toolbox.testButton2->getPosition());

    Texture test3Texture; // Makes the sprite for the test case 3 button
    test3Texture.loadFromFile("../images/test_3.png");
    Sprite test3Sprite;
    test3Sprite.setTexture(test3Texture);
    test3Sprite.setPosition(toolbox.testButton3->getPosition());

    Texture digits; // Loads the whole image data of digits into one texture
    digits.loadFromFile("../images/digits.png");

    int numFlags = toolbox.gameState->getFlagCount(); // Keeps track of the number of flags at a current time based ont the number of mines

    // Creates a 11 int rects which hold the position of each digit as a whole to more quickly switch the texture on the 3 different sprites
    IntRect zero(0, 0, 21, 32);
    IntRect one(21, 0, 21, 32);
    IntRect two(21*2, 0, 21, 32);
    IntRect three(21*3, 0, 21, 32);
    IntRect four(21*4, 0, 21, 32);
    IntRect five(21*5, 0, 21, 32);
    IntRect six(21*6, 0, 21, 32);
    IntRect seven(21*7, 0, 21, 32);
    IntRect eight(21*8, 0, 21, 32);
    IntRect nine(21*9, 0, 21, 32);
    IntRect minus(21*10, 0, 21, 32);

    // Three main int rects which represent the three main digits that appear
    IntRect rectLeft;
    IntRect rectMiddle;
    IntRect rectRight;

    // calculates the numbers for the 3 sprites on when it first apears
    int ones = abs(numFlags % 10);
    int tens = abs((numFlags/10)%10);
    int hundreds = abs((numFlags/100)%10);
    if(ones == 0){ // If to change the int rect of the right digit
        rectRight = zero;
    }else if(ones == 1){
        rectRight = one;
    }else if(ones == 2){
        rectRight = two;
    }else if (ones == 3){
        rectRight = three;
    }else if (ones == 4){
        rectRight = four;
    }else if (ones == 5){
        rectRight = five;
    }else if (ones == 6){
        rectRight = six;
    }else if (ones == 7){
        rectRight = seven;
    }else if (ones == 8){
        rectRight = eight;
    }else if (ones == 9){
        rectRight = nine;
    }
    if(tens == 0){ // If to change the int rect of the middle digit
        rectMiddle = zero;
    }else if(tens == 1){
        rectMiddle = one;
    }else if(tens == 2){
        rectMiddle = two;
    }else if (tens == 3){
        rectMiddle = three;
    }else if (tens == 4){
        rectMiddle = four;
    }else if (tens == 5){
        rectMiddle = five;
    }else if (tens == 6){
        rectMiddle = six;
    }else if (tens == 7){
        rectMiddle = seven;
    }else if (tens == 8){
        rectMiddle = eight;
    }else if (tens == 9){
        rectMiddle = nine;
    }
    if(hundreds == 0){ // If to change the int rect of the left digit
        rectLeft = zero;
    }else if(hundreds == 1){
        rectLeft = one;
    }else if(hundreds == 2){
        rectLeft = two;
    }else if (hundreds == 3){
        rectLeft = three;
    }else if (hundreds == 4){
        rectLeft = four;
    }else if (hundreds == 5){
        rectLeft = five;
    }else if (hundreds == 6){
        rectLeft = six;
    }else if (hundreds == 7){
        rectLeft = seven;
    }else if (hundreds == 8){
        rectLeft = eight;
    }else if (hundreds == 9){
        rectLeft = nine;
    }

    if(numFlags < 0){ // checks if the left number has to be minus to be negative
        rectLeft = minus;
    }

    //sets all three number sprites based on the int rect that was set before
    Sprite leftD(digits);
    leftD.setTextureRect(rectLeft);
    leftD.setPosition(0, 32*sizeY);
    Sprite middleD(digits);
    middleD.setTextureRect(rectMiddle);
    middleD.setPosition(21, 32*sizeY);
    Sprite rightD(digits);
    rightD.setTextureRect(rectRight);
    rightD.setPosition(42, 32*sizeY);

    // Loads the win and lose face
    Texture winFace;
    winFace.loadFromFile("../images/face_win.png");
    Texture loseFace;
    loseFace.loadFromFile("../images/face_lose.png");
    int points = 0; // points keep track to see if the player wins or looses (wins if points reaches 400)

    int toggleClicks = 0; // checks the number of times that toggle debug mode is clicked

    Event event; // keep track of mouse clicks and events
    float currX, currY; // Keeps track of the mouse position
    while(toolbox.window.isOpen()){ // opens and holds open the toolbox window while the X is not pressed
        Vector2i pos = Mouse::getPosition(toolbox.window); // gets the mouse position and makes it into a vector2i
        currX = pos.x/32.0; // calculates the x position of the mouse based on the tiles instead of the pixels
        currY = pos.y/32.0; // calculates the y position of the mouse based on the tiles instead of the pixels
        while (toolbox.window.pollEvent(event)){ // polls events that are checking different things while the window is open
            if(event.type == Event::EventType::Closed){ // checks if the X at the top is clicked and if it is it closes the window
                toolbox.window.close(); // closes the window
            }
            // Very weird thingy happening here with the rubric: if you turn off debugmode then you lose but if you lose
            // then you are only allowed to click the dead face to restart so i did it how i thought was right
            if(event.type == Event::MouseButtonPressed && toolbox.gameState->getPlayStatus() != GameState::LOSS){ // If the mouse is pressed in any area of the window and the gamestate is not loss
                if(event.key.code == Mouse::Left && currY < sizeY){ // Checks if the click was a left click and on one of the tiles
                    toolbox.gameState->getTile(int(currX), int(currY))->onClickLeft(); // calls the tiles left click function
                }else if (event.key.code == Mouse::Right && currY < sizeY){ // checks if the click was a right click and on a tile
                    if (toolbox.gameState->getTile(int(currX), int(currY))->getState() == Tile::FLAGGED){ // if the tile right-clicked on was flagged then num flags increases
                        numFlags++;
                    }else if (toolbox.gameState->getTile(int(currX), int(currY))->getState() == Tile::HIDDEN){ // else if its hidden then it decreases
                        numFlags--;
                    }

                    toolbox.gameState->getTile(int(currX), int(currY))->onClickRight(); // Then calls the right click method based on the tile clicked on

                    int ones = abs(numFlags % 10); // Calculates the ones place of the num flags
                    int tens = abs((numFlags/10)%10); // Calculates the tens place of the num flags
                    int hundreds = abs((numFlags/100)%10); // Calculates the hundreds place of the num flags
                    // Sets the corresponding number to the calculates place for ones
                    if(ones == 0){
                        rectRight = zero;
                    }else if(ones == 1){
                        rectRight = one;
                    }else if(ones == 2){
                        rectRight = two;
                    }else if (ones == 3){
                        rectRight = three;
                    }else if (ones == 4){
                        rectRight = four;
                    }else if (ones == 5){
                        rectRight = five;
                    }else if (ones == 6){
                        rectRight = six;
                    }else if (ones == 7){
                        rectRight = seven;
                    }else if (ones == 8){
                        rectRight = eight;
                    }else if (ones == 9){
                        rectRight = nine;
                    }
                    // Sets the corresponding number to the calculates place for tens
                    if(tens == 0){
                        rectMiddle = zero;
                    }else if(tens == 1){
                        rectMiddle = one;
                    }else if(tens == 2){
                        rectMiddle = two;
                    }else if (tens == 3){
                        rectMiddle = three;
                    }else if (tens == 4){
                        rectMiddle = four;
                    }else if (tens == 5){
                        rectMiddle = five;
                    }else if (tens == 6){
                        rectMiddle = six;
                    }else if (tens == 7){
                        rectMiddle = seven;
                    }else if (tens == 8){
                        rectMiddle = eight;
                    }else if (tens == 9){
                        rectMiddle = nine;
                    }
                    // Sets the corresponding number to the calculates place for hundreds
                    if(hundreds == 0){
                        rectLeft = zero;
                    }else if(hundreds == 1){
                        rectLeft = one;
                    }else if(hundreds == 2){
                        rectLeft = two;
                    }else if (hundreds == 3){
                        rectLeft = three;
                    }else if (hundreds == 4){
                        rectLeft = four;
                    }else if (hundreds == 5){
                        rectLeft = five;
                    }else if (hundreds == 6){
                        rectLeft = six;
                    }else if (hundreds == 7){
                        rectLeft = seven;
                    }else if (hundreds == 8){
                        rectLeft = eight;
                    }else if (hundreds == 9){
                        rectLeft = nine;
                    }
                    // Sees if the number is negative and changes the int rect accordingly
                    if(numFlags < 0){
                        rectLeft = minus;
                    }

                    leftD.setTextureRect(rectLeft); // sets the texture based off of the previously created int rect of the left digit
                    middleD.setTextureRect(rectMiddle); // sets the texture based off of the previously created int rect of the middle digit
                    rightD.setTextureRect(rectRight); // sets the texture based off of the previously created int rect of the right digit

                }else if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 11.5 && currX < 13.5){ // Sees if the new game button was clicked
                    toolbox.newGameButton->onClick(); // Calls the new game button's on click function
                }else if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 15.5 && currX < 17.5){ // Sees if the debug button was clicked
                    toolbox.debugButton->onClick(); // Calls the debug buttons function
                    toggleClicks++;
                    if(toggleClicks >= 2){
                        newGameSprite.setTexture(loseFace);
                    }
                    std::cout << getDebugMode();
                }else if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 17.5 && currX < 19.5){ // Sees if the test one button was clicked
                    toolbox.gameState->setPlayStatus(GameState::WIN); // Sets game states state to win for the if in restart
                    toolbox.testButton1->onClick(); // Calls the test 1 buttons function
                }else if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 19.5 && currX < 21.5){ // Sees if the test two button was clicked
                    toolbox.gameState->setPlayStatus(GameState::LOSS); // Sets game states state to loss for the if in restart
                    toolbox.testButton2->onClick(); // Calls the test 2 buttons function
                }else if(event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 21.5 && currX < 23.5){ // Sees if the test three button was clicked
                    toolbox.gameState->setPlayStatus(GameState::PLAYING); // Sets game states state to playing for the if in restart
                    toolbox.testButton3->onClick(); // Calls the test 3 buttons function
                }

                points = 0; // Resets points to check win condition
                for(int i = 0; i < sizeX; i++){ // 2d loop through the grid of tiles
                    for(int j = 0; j < sizeY; j++){
                        if(toolbox.gameState->getTile(i, j)->getState() == Tile::REVEALED && !toolbox.gameState->getTile(i, j)->getMine()){
                            points++; // increases points by one if the tile is revealed and does not have a mine
                        }else if((toolbox.gameState->getTile(i, j)->getState() == Tile::HIDDEN || toolbox.gameState->getTile(i, j)->getState() == Tile::FLAGGED) && toolbox.gameState->getTile(i, j)->getMine()){
                            points++; // increases points if the tile is hidden or flagged and does have a mine
                        }
                    }
                }
                if(points == 400){ // If the points = 400 then the face texture changes
                    newGameSprite.setTexture(winFace); // face sprite changes to win face
                }
                for(int i = 0; i < sizeX; i++){ // 2d loop through grid of tiles
                    for(int j = 0; j < sizeY; j++){
                        if(toolbox.gameState->getTile(i, j)->getState() == Tile::EXPLODED && !getDebugMode()){
                            newGameSprite.setTexture(loseFace); // If theres a exploded and revealed tile while debug mode is off then the face changes to the loss face
                            for(int x = 0; x < sizeX; x++){
                                for(int y = 0; y < sizeY; y++){
                                    if(toolbox.gameState->getTile(x, y)->getMine()){
                                        toolbox.gameState->getTile(x, y)->setState(Tile::EXPLODED);
                                    }
                                }
                            }
                        }
                    }
                }

            }else{ // Makes sure that there is no other possible interactions with the game after a loss other than starting a new random game by clicking the dead face
                if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 11.5 && currX < 13.5){ // if loss and if click on restart then restart
                    toolbox.newGameButton->onClick();
                }else if (event.key.code == Mouse::Left && currY >= 16 && currY < 18 && currX > 15.5 && currX < 17.5){ // if loss and if click on debug then debug
                    if(toggleClicks % 2 == 0){ // only call toggle clicks on the second click
                        toolbox.debugButton->onClick();
                        toolbox.gameState->setPlayStatus(GameState::LOSS);
                        if(toggleClicks >= 2){
                            newGameSprite.setTexture(loseFace);
                        }
                    }
                    toggleClicks++; // increment
                }
            }
        }
        toolbox.window.clear(Color::White); // clears the window to be white
        // Creates and draws all the tiles

        for(int i = 0; i < sizeX; i++) { // 2d loop through tiles
            for (int j = 0; j < sizeY; j++) {
                toolbox.gameState->getTile(i, j)->draw(); // calls each tiles draw function and properly draws it to the toolbox window
            }
        }
        toolbox.window.draw(newGameSprite); // draws the new game face sprite
        toolbox.window.draw(debugSprite); // draws the debug sprite
        toolbox.window.draw(test1Sprite); // draws the test 1 sprite
        toolbox.window.draw(test2Sprite); // draws the test 2 sprites
        toolbox.window.draw(test3Sprite); // draws the test 3 sprites

        toolbox.window.draw(leftD); // Draws the left digit sprites
        toolbox.window.draw(middleD); // Draws the middle digits
        toolbox.window.draw(rightD); // Draws the right digits

        toolbox.window.display(); // Displays the whole texture onto the window

    }
}


void toggleDebugMode() { // Toggle the debug mode on/off
    Toolbox& toolbox = Toolbox::getInstance(); // gets the instance of the toolbox singleton
    debugMode = !debugMode; // Changes debug mode bool
    if(debugMode){ // if debug mode is on then it loops through the 2d grid and explodes all the mines
        for(int i = 0; i < toolbox._dimentions().x; i++){
            for(int j = 0; j < toolbox._dimentions().y; j++){
                if(toolbox.gameState->getTile(i, j)->getMine()){
                    toolbox.gameState->getTile(i, j)->setState(Tile::EXPLODED);
                }
            }
        }
    }else{ // else if its off then it hides all the mines
        for(int i = 0; i < toolbox._dimentions().x; i++){
            for(int j = 0; j < toolbox._dimentions().y; j++){
                if(toolbox.gameState->getTile(i, j)->getMine()){
                    toolbox.gameState->getTile(i, j)->setState(Tile::HIDDEN);
                }
            }
        }
    }
}

bool getDebugMode() { // Return the current state of debug mode
    return debugMode;
}
