#ifndef SIMPLEGAME_ENTITY_H
#define SIMPLEGAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Sprite {
private:
    int lives;
    float speed{};
    float acceleration{};
    float initial_X{};
    float initial_Y{};

public:
    Entity(const sf::Texture& texture,
           float scale,
           float initial_X,
           float initial_Y,
           int lives,
           float speed,
           float acceleration);

    float getSpeed() const;

    bool isAlive() const;

    float getInitial_X() const;

    float getInitial_Y() const;

    void setInitialPosition(float initial_X, float initial_Y);

    int getLives() const;

    void setLives(int lives);

    void setSpeed(float speed);

    float getWidth();

    float getHeight();
    
    void accelerate(int X, int Y, int Z);
};

#endif //SIMPLEGAME_ENTITY_H
