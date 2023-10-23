#ifndef SIMPLEGAME_ENTITY_H
#define SIMPLEGAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Sprite {
private:
    int lives;
    float speed_X{};
    float speed_Y{};
    float acceleration{};
    float initial_X{};
    float initial_Y{};

public:
    Entity(const sf::Texture& texture,
           float scale,
           float initial_X,
           float initial_Y,
           int lives,
           float speed_X,
           float speed_Y,
           float acceleration);

    float getSpeed_X() const;

    float getSpeed_Y() const;

    bool isAlive() const;

    float getInitial_X() const;

    float getInitial_Y() const;

    void setInitialPosition(float initial_X, float initial_Y);

    int getLives() const;

    void setLives(int lives);

    void setSpeed_X(float speed_X);

    void setSpeed_Y(float speed_Y);

    void setAcceleration(float acceleration);

    float getWidth();

    float getHeight();
    
    void accelerate(int X, int Y, int Z, float deltaTime);
};

#endif //SIMPLEGAME_ENTITY_H
