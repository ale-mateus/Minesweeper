#include "Tile.h"
#include "Toolbox.h"

using namespace sf;

Tile::Tile(sf::Vector2f position){ // Tile constructor
    Tile::state = HIDDEN;
    Tile::position = position;
    containsMine = false;
    surrounded = 0;
}

sf::Vector2f Tile::getLocation() { // returns the location of the tile
    return position;
}

Tile::State Tile::getState() { // returns the state of the tile
    return state;
}

std::array<Tile*, 8> &Tile::getNeighbors() { // returns the neighbors of  the
    return neighbors;
}

void Tile::setState(State newState) { // sets the state of the tile and sets the sprite
    Toolbox& toolbox = Toolbox::getInstance();
    state = newState;
    if(newState == HIDDEN){
        sf::Texture texture;
        texture.loadFromFile("../images/tile_hidden.png");
        sprite.setTexture(texture);
    }else if(newState == REVEALED){
        sf::Texture texture;
        texture.loadFromFile("../images/tile_revealed.png");
        sprite.setTexture(texture);
    }else if(newState == FLAGGED){
        sf::Texture texture;
        texture.loadFromFile("../images/flag.png");
        sprite.setTexture(texture);
    }else if(newState == EXPLODED){
        sf::Texture texture;
        texture.loadFromFile("../images/mine.png");
        sprite.setTexture(texture);
        toolbox.gameState->setPlayStatus(toolbox.gameState->LOSS);
    }
}

void Tile::setNeighbors(std::array<Tile*, 8> newNeighbors) { // returns the neighbors
    neighbors = newNeighbors;
}

void Tile::onClickLeft() { // changes the sprite of the tile based on the tiles mine status
    if (state == HIDDEN) {
        // Check if the tile contains a mine
        if (containsMine) {
            setState(EXPLODED);
        } else {
            setState(REVEALED);
            revealNeighbors();

            // Tile does not contain a mine, continue with revealing logic
        }
    }
}

void Tile::onClickRight() { // changes the sprite of the tile from flagged to hidden
    if(this->state == HIDDEN){
        setState(FLAGGED);
    }else if(this->state == FLAGGED){
        setState(HIDDEN);
    }
}

void Tile::draw() { // draws a tile according to the features of the tile
    Toolbox& toolbox = Toolbox::getInstance();

    // Add logic for drawing the tile based on its state and sprite
    Texture tileTypeTexture;
    Texture frontTexture;
    Sprite tileTypeSprite;
    Sprite frontSprite;

    if(state == HIDDEN){ // checks if it is hidden and then sets the correct texture and draws it onto the window
        tileTypeTexture.loadFromFile("../images/tile_hidden.png");
        tileTypeSprite.setTexture(tileTypeTexture);
        tileTypeSprite.setPosition(position);
        toolbox.window.draw(tileTypeSprite);
    }else if(state == REVEALED){ // checks if it is revealed and then sets the correct texture
        int counter = 0; // counter used to see how many mines are around the tile
        for (int i = 0; i < 8; i++){ // loop through the neighbors to see if they have mines to place the correct number
            if(neighbors[i] != nullptr && neighbors[i]->containsMine){
                counter++;
            }
        }
        if(counter == 0){ // places the revealed tile with the correct number 0-8 and draws it onto the window
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            tileTypeSprite.setTexture(tileTypeTexture);
            tileTypeSprite.setPosition(position);
            toolbox.window.draw(tileTypeSprite);
        }else if (counter == 1){
            RenderTexture one;
            one.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_1.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            one.draw(tileTypeSprite);
            one.draw(frontSprite);

            Texture oneTexture = one.getTexture();
            Image oneImg = oneTexture.copyToImage();
            oneImg.flipVertically();
            oneTexture.loadFromImage(oneImg);
            Sprite oneSprite(oneTexture);
            oneSprite.setPosition(position);
            toolbox.window.draw(oneSprite);
        }else if (counter == 2){
            RenderTexture two;
            two.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_2.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            two.draw(tileTypeSprite);
            two.draw(frontSprite);

            Texture twoTexture = two.getTexture();
            Image twoImg = twoTexture.copyToImage();
            twoImg.flipVertically();
            twoTexture.loadFromImage(twoImg);
            Sprite twoSprite(twoTexture);
            twoSprite.setPosition(position);
            toolbox.window.draw(twoSprite);
        }else if (counter == 3){
            RenderTexture three;
            three.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_3.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            three.draw(tileTypeSprite);
            three.draw(frontSprite);

            Texture threeTexture = three.getTexture();
            Image threeImg = threeTexture.copyToImage();
            threeImg.flipVertically();
            threeTexture.loadFromImage(threeImg);
            Sprite threeSprite(threeTexture);
            threeSprite.setPosition(position);
            toolbox.window.draw(threeSprite);
        } else if (counter == 4){
            RenderTexture four;
            four.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_4.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            four.draw(tileTypeSprite);
            four.draw(frontSprite);

            Texture fourTexture = four.getTexture();
            Image fourImg = fourTexture.copyToImage();
            fourImg.flipVertically();
            fourTexture.loadFromImage(fourImg);
            Sprite fourSprite(fourTexture);
            fourSprite.setPosition(position);
            toolbox.window.draw(fourSprite);
        } else if(counter == 5){
            RenderTexture five;
            five.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_5.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            five.draw(tileTypeSprite);
            five.draw(frontSprite);

            Texture fiveTexture = five.getTexture();
            Image fiveImg = fiveTexture.copyToImage();
            fiveImg.flipVertically();
            fiveTexture.loadFromImage(fiveImg);
            Sprite fiveSprite(fiveTexture);
            fiveSprite.setPosition(position);
            toolbox.window.draw(fiveSprite);
        } else if (counter == 6){
            RenderTexture six;
            six.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_6.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            six.draw(tileTypeSprite);
            six.draw(frontSprite);

            Texture sixTexture = six.getTexture();
            Image sixImg = sixTexture.copyToImage();
            sixImg.flipVertically();
            sixTexture.loadFromImage(sixImg);
            Sprite sixSprite(sixTexture);
            sixSprite.setPosition(position);
            toolbox.window.draw(sixSprite);
        } else if (counter == 7){
            RenderTexture seven;
            seven.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_7.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            seven.draw(tileTypeSprite);
            seven.draw(frontSprite);

            Texture sevenTexture = seven.getTexture();
            Image sevenImg = sevenTexture.copyToImage();
            sevenImg.flipVertically();
            sevenTexture.loadFromImage(sevenImg);
            Sprite sevenSprite(sevenTexture);
            sevenSprite.setPosition(position);
            toolbox.window.draw(sevenSprite);
        } else if (counter == 8){
            RenderTexture eight;
            eight.create(32, 32);
            tileTypeTexture.loadFromFile("../images/tile_revealed.png");
            frontTexture.loadFromFile("../images/number_8.png");

            tileTypeSprite.setTexture(tileTypeTexture);
            frontSprite.setTexture(frontTexture);

            eight.draw(tileTypeSprite);
            eight.draw(frontSprite);

            Texture eightTexture = eight.getTexture();
            Image eightImg = eightTexture.copyToImage();
            eightImg.flipVertically();
            eightTexture.loadFromImage(eightImg);
            Sprite eightSprite(eightTexture);
            eightSprite.setPosition(position);
            toolbox.window.draw(eightSprite);
        }

    }else if(state == FLAGGED){ //Sets the texture of the sprite to have a flag on top of the hidden state and draws it onto the window
        RenderTexture flagged;
        flagged.create(32, 32);
        tileTypeTexture.loadFromFile("../images/tile_hidden.png");
        frontTexture.loadFromFile("../images/flag.png");

        tileTypeSprite.setTexture(tileTypeTexture);
        frontSprite.setTexture(frontTexture);

        flagged.draw(tileTypeSprite);
        flagged.draw(frontSprite);

        Texture flaggedTexture = flagged.getTexture();
        Image flaggedImg = flaggedTexture.copyToImage();
        flaggedImg.flipVertically();
        flaggedTexture.loadFromImage(flaggedImg);
        Sprite flaggedSprite(flaggedTexture);
        flaggedSprite.setPosition(position);
        toolbox.window.draw(flaggedSprite);
    }else{ // Sets the texture of the tile to have a mine on it and draws it onto the window
        RenderTexture exploded;
        exploded.create(32, 32);
        tileTypeTexture.loadFromFile("../images/tile_revealed.png");
        frontTexture.loadFromFile("../images/mine.png");

        tileTypeSprite.setTexture(tileTypeTexture);

        frontSprite.setTexture(frontTexture);

        exploded.draw(tileTypeSprite);
        exploded.draw(frontSprite);

        Texture explodedTexture = exploded.getTexture();
        Image explodedImg = explodedTexture.copyToImage();
        explodedImg.flipVertically();
        explodedTexture.loadFromImage(explodedImg);
        Sprite explodedSprite(explodedTexture);

        explodedSprite.setPosition(position);

        toolbox.window.draw(explodedSprite);
    }

}

void Tile::revealNeighbors() { // reveals the neighbors using recursion to make sure the spread of the open is correct
    for (Tile* neighbor : neighbors) { // for each loop for the neighbors
        for(int i = 0; i < 8;i++){ // loops through the neighbors to see which one has a mine in it
            if(neighbors[i] != nullptr && neighbors[i]->containsMine){
                surrounded++; // increments to show that there is a mine around the neighbor tile
            }
        }
        if (neighbor != nullptr && !neighbor->containsMine && neighbor->getState() == HIDDEN && surrounded == 0) { // makes sure the neighbor is aplicable to be revealed
            neighbor->setState(REVEALED);
            // Recursive call to reveal neighbors of the neighbor
            neighbor->revealNeighbors(); // recursion
        }
    }
}

void Tile::setMine(){ // sets the bool value contains mine to true
    containsMine = true;
}

bool Tile::getMine() { // returns the value of contains mine
    return containsMine;
}