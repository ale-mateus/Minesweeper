#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick){ // default constructor
    position = _position;
    onClickCallBack = _onClick;
};

sf::Vector2f Button::getPosition(){ // returns the position of the button
    return position;
}

sf::Sprite* Button::getSprite(){ // returns the sprite of the button
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite){ // sets the buttons sprite
    sprite = _sprite;
}

void Button::onClick(){ // calls the method that the button corresponds to
    onClickCallBack();
}