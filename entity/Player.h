//
// Created by neo on 10/20/23.
//

#ifndef SIMPLEGAME_PLAYER_H
#define SIMPLEGAME_PLAYER_H

#include <SFML/Graphics/Texture.hpp>

class Player : public sf::Sprite {
private:
    int lives;
    float speed{};
    float initialPosition{};
public:
    int getLives() const;
    Player(const sf::Texture& texture,
           float scale,
           float initialPosition,
           int lives);

    float getSpeed() const;

    bool isAlive() const;

    float getInitialPosition() const;

    void setLives(int lives);

    void setSpeed(float speed);
};

#endif //SIMPLEGAME_PLAYER_H
