#ifndef SIMPLEGAME_ENTITY_H
#define SIMPLEGAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Sprite {
private:
    float initialScale_X{};
    float initialScale_Y{};
    float scale_X{};
    float scale_Y{};
    int lives{};
    float speed_X{};
    float speed_Y{};
    float acceleration{};
    float initial_X{};
    float initial_Y{};
    bool isJumping{};

public:
    Entity(const sf::Texture& texture,
           float scale,
           float initial_X,
           float initial_Y,
           int lives,
           float speed_X,
           float speed_Y,
           float acceleration);

    float getInitialScale_X() const;

    float getInitialScale_Y() const;

    float getInitial_X() const;

    float getInitial_Y() const;

    int getLives() const;

    float getSpeed_X() const;

    float getSpeed_Y() const;

    float getWidth();

    float getHeight();

    void setScale(float scale_X, float scale_Y);

    void setInitialPosition(float initial_X, float initial_Y);

    void setLives(int lives);

    void setSpeed_X(float speed_X);

    void setSpeed_Y(float speed_Y);

    void setAcceleration(float acceleration);

    bool isAlive() const;

    void accelerate(int X, int Y, int Z, float deltaTime);

    bool jump(float deltaTime, float initialSpeed_Y);

    void setIsJumping(bool isJumping);

    bool getIsJumping();
};

#endif //SIMPLEGAME_ENTITY_H
