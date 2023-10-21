#ifndef SIMPLEGAME_ENTITY_H
#define SIMPLEGAME_ENTITY_H

#include <SFML/Graphics/Texture.hpp>

class Entity : public sf::Sprite {
private:
    int lives;
    float speed{};
    float initialPosition{};

public:
    int getLives() const;
    Entity(const sf::Texture& texture,
           float scale,
           float initialPosition,
           int lives,
           float speed);

    float getSpeed() const;

    bool isAlive() const;

    float getInitialPosition() const;

    void setLives(int lives);

    void setSpeed(float speed);

    float getWidth();

    float getHeight();
};

#endif //SIMPLEGAME_ENTITY_H
