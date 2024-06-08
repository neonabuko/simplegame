#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

class Entity : public sf::Sprite {
private:
    int lives{};
    float speed_X{};
    float speed_Y{};
    float acceleration{};
    bool isJumping{};
    bool isReverse{};
    bool isShooting{};
    bool isPowerup{};
    bool isBig{};

public:
    Entity();

    Entity(int lives, float speed_X, float speed_Y, float acceleration);
    
    int getLives();
    float getAcceleration();
    float getWidth();
    float getHeight();
    float getSpeed_X();
    float getSpeed_Y();
    bool getIsJumping();
    bool getIsReverse();
    bool getIsShooting();
    bool getIsAlive() const;

    void incrementLives(int lives);
    void setSpeed_X(float speed_X);
    void setSpeed_Y(float speed_Y);
    void setAcceleration(float acceleration);
    void setIsReverse(bool isReverse);
    void setIsJumping(bool isJumping);
    void setIsShooting(bool isShooting);
    
    void grow();
    void accelerate();

    void update();
    void resetGame();
};

#endif
