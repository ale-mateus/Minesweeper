#ifndef PROJECT4V2_TILE_H
#define PROJECT4V2_TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>


class Tile{
public:
    Tile(sf::Vector2f position); // Constructs a new tile object at the designated _position.
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED }; // Represents tile’s current UI state (visualization).
    sf::Vector2f getLocation(); // returns the location of the tile
    State getState(); //Returns current state of this tile.
    std::array<Tile*, 8>& getNeighbors(); // Returns pointer to array of Tile pointers surrounding the specified tile
    void setState(State _state); //Sets the state of this tile and changes the sprite
    void setNeighbors(std::array<Tile*, 8> _neighbors); // Populates the neighboring tiles
    void onClickLeft(); // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries based on its state
    void onClickRight(); // Toggles this tile’s state between FLAGGED and HIDDEN and changes sprite
    void draw(); // Render this tile to the screen according to is state
    void setMine(); // changes the bool value of contains mine to true
    bool getMine(); // returns if the tile has a mine

protected:
    void revealNeighbors(); // Based on State and mine content of the tile neighbors, set their state to REVEALED.

private:
    bool containsMine; // bool to represent if the tile has a mine or not
    sf::Vector2f position; // holds the position of the tile
    State state; // holds the state of the tile
    std::array<Tile*, 8> neighbors; // holds the neighbors of the tile
    sf::Sprite sprite; // holds the sprite of the tile
    int surrounded; // counts how many mines are around this one mine
};

#endif //PROJECT4V2_TILE_H
