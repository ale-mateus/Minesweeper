#ifndef PROJECT4V2_GAMESTATE_H
#define PROJECT4V2_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    // Constructors
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);

    // Public member functions
    int getFlagCount() const;
    int getMineCount() const;
    Tile* getTile(int x, int y) const;
    PlayStatus getPlayStatus() const;
    void setPlayStatus(PlayStatus _status);

private:
    // Private member functions
    void initializeRandomState();
    void initializeFromFile(const char* filepath);

    // Private data members
    sf::Vector2i dimensions;
    int numberOfMines;
    int flagCount;
    int mineCount;
    PlayStatus playStatus;
    Tile* grid[25][16];// 2D array of Tile pointers
    // Destructor
    ~GameState();
};


#endif //PROJECT4V2_GAMESTATE_H
