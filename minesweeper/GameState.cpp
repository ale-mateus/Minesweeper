#include "GameState.h"
#include "fstream"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) // default constructor
        : dimensions(_dimensions), numberOfMines(_numberOfMines), flagCount(_numberOfMines), playStatus(PlayStatus::PLAYING) {
    // Initialize the state based on the dimensions and number of mines
    initializeRandomState(); // calls a private function that sets up the default constructor
}

GameState::GameState(const char* filepath) : flagCount(0), mineCount(0), playStatus(PlayStatus::PLAYING) { // file based constructor
    // Initialize the state based on the file
    initializeFromFile(filepath); // calls private function that sets up the file constructor
}

GameState::~GameState() { // private destructor for gamestate
    // Release memory for tiles
    for (int i = 0; i < dimensions.x; ++i) {
        for (int j = 0; j < dimensions.y; ++j) {
            delete grid[i][j];
        }
    }
}

int GameState::getFlagCount() const { // returns the flag count
    return flagCount;
}

int GameState::getMineCount() const { // returns the number of mines
    return numberOfMines;
}

Tile* GameState::getTile(int x, int y) const { // returns the tile at a spesific part in the grid
    // Check if coordinates are within bounds
    if (x >= 0 && x < dimensions.x && y >= 0 && y < dimensions.y) {
        return grid[x][y];
    }
    return nullptr;
}

GameState::PlayStatus GameState::getPlayStatus() const { // returns the games playstatus
    return playStatus;
}

void GameState::setPlayStatus(PlayStatus _status) { // sets the playstatus
    playStatus = _status;
}

void GameState::initializeRandomState() { // initializes the random gamstate
    // Makes a grid of Tiles
    sf::Vector2f tilePosition(0, 0);
    for(int i = 0; i < dimensions.x; i++){ // loops through the grid and makes a new tile for the dimentions
        for(int j = 0; j < dimensions.y; j++){
            grid[i][j] = (new Tile(tilePosition));
            tilePosition.y += 32;
            if(tilePosition.y >= 32*16){
                tilePosition.y = 0;
                tilePosition.x += 32;
            }
        }
    }
    // Sets Mines
    mineCount = 0;
    while(mineCount < numberOfMines){ // loops through and sets the mines
        for (int i = 0; i < dimensions.x; i++) {
            for (int j = 0; j < dimensions.y; j++) {
                if (rand() % 400 == 0 && mineCount < numberOfMines && !grid[i][j]->getMine()) {
                    mineCount++;
                    grid[i][j]->setMine();
                }
            }
        }
    }
    // Gets Neighbors
    int counter = 0;
    for (int x = 0; x < dimensions.x; ++x) { // loops through the grid and sets the neighbors making sure that there is no neighbor then it is a nullptr
        for (int y = 0; y < dimensions.y; ++y) {
            // Makes an array of neighbors for the current tile
            std::array<Tile*, 8> neighbors;

            // Check and set neighbors for the current tile
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    // Skip the current tile itself
                    if (i == 0 && j == 0) {
                        continue;
                    }

                    int neighborX = x + i;
                    int neighborY = y + j;

                    // Check if the neighbor coordinates are within bounds
                    if (neighborX >= 0 && neighborX < dimensions.x &&
                        neighborY >= 0 && neighborY < dimensions.y) {
                        // Set the neighbor for the current tile
                        neighbors[counter] = grid[neighborX][neighborY];
                    }else{
                        neighbors[counter] = nullptr;
                    }

                    counter++;
                }
            }
            counter = 0;
            grid[x][y]->setNeighbors(neighbors);
        }
    }
}

void GameState::initializeFromFile(const char* filepath) { // initializes from the file

    std::ifstream fileBoard; // Makes an ifstream
    fileBoard.open(filepath);
    std::string myString; // makes a string to hold what is in the file

    if(fileBoard.is_open()){
        // makes a board

        sf::Vector2f tilePosition(0, 0);

        int y = 0;
        int x = 0;
        //Gets dimentions
        while (std::getline(fileBoard, myString) && myString != "") {
            y++;
            x = myString.length();
        }

        fileBoard.close();
        fileBoard.open(filepath);

        sf::Vector2i fileDimensions(x, y);
        dimensions = fileDimensions;

        for(int i = 0; i < dimensions.x; i++){ // makes the new grid the size of the file
            for(int j = 0; j < dimensions.y; j++){
                grid[i][j] = (new Tile(tilePosition));
                tilePosition.y += 32;
                if(tilePosition.y >= 32*16){
                    tilePosition.y = 0;
                    tilePosition.x += 32;
                }
            }
        }

        flagCount = 0;
        mineCount = 0;
        //sets mines
        char ch; // sets a mine on where there is a one
        for(int i = 0; i < dimensions.y; i++){
            for(int j = 0; j < dimensions.x; j++){
                fileBoard >> ch;
                if (ch - 48 == 1){
                    mineCount++;
                    grid[j][i]->setMine();
                    flagCount++;
                    mineCount++;
                }
            }
        }

        int counter = 0; // keeps track of which neighbor she is in
        for (int x = 0; x < dimensions.x; ++x) {
            for (int y = 0; y < dimensions.y; ++y) {
                // Makes an array of neighbors for the current tile
                std::array<Tile*, 8> neighbors;

                // Check and set neighbors for the current tile
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        // Skip the current tile itself
                        if (i == 0 && j == 0) {
                            continue;
                        }

                        int neighborX = x + i;
                        int neighborY = y + j;

                        // Check if the neighbor coordinates are within bounds
                        if (neighborX >= 0 && neighborX < dimensions.x &&
                            neighborY >= 0 && neighborY < dimensions.y) {
                            // Set the neighbor for the current tile
                            neighbors[counter] = grid[neighborX][neighborY];
                        }else{
                            neighbors[counter] = nullptr;
                        }
                        counter++;
                    }
                }
                counter = 0;
                grid[x][y]->setNeighbors(neighbors); // sets the neighbors
            }
        }

    }
}