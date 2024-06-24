#ifndef PROJECT4V2_TOOLBOX_H
#define PROJECT4V2_TOOLBOX_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"

using namespace sf;

class Toolbox {
public:
    static Toolbox& getInstance(); // returns the instance of the toolbox

    RenderWindow window; // the window for the main render window
    GameState* gameState; // grates a gamestate for the game
    Button* debugButton; // button constructor for the debug mode
    Button* newGameButton; // button constructor for the new game mode
    Button* testButton1; // button constructor for the test 1 mode
    Button* testButton2; // button constructor for the test 2 mode
    Button* testButton3; // button constructor for the test 3 mode
    Vector2i _dimentions();

private:
    Toolbox(); // toolbox constructor
};


#endif //PROJECT4V2_TOOLBOX_H
