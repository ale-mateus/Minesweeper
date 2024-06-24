#ifndef PROJECT4V2_BUTTON_H
#define PROJECT4V2_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    // Instance Variables
    sf::Vector2f position;
    std::function<void(void)> onClickCallBack;
    sf::Sprite *sprite;

    // Class Constructor
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    // Class Methods
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};


#endif //PROJECT4V2_BUTTON_H
