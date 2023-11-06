#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

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
    bool isReverse{};
    bool isShooting{};
    bool isPowerup{};
    bool isBig{};
    sf::Sound jump;
    sf::Sound stompLight;

public:
    Entity();

    Entity(
        float initial_X,
        float initial_Y,
        int lives,
        float speed_X,
        float speed_Y,
        float acceleration
        );
    
    float getInitialScale_X() const;
    float getInitialScale_Y() const;
    float getInitial_X() const;
    float getInitial_Y() const;
    int getLives() const;
    float getSpeed_X() const;
    float getSpeed_Y() const;
    float getWidth();
    float getHeight();
    bool getIsReverse();
    bool getIsJumping();
    bool getIsAlive() const;
    bool getIsShooting();
    bool getIsPowerup();
    bool getIsBig();

    void setScale(float scale_X, float scale_Y);
    void setInitialPosition(float initial_X, float initial_Y);
    void setLives(int lives);
    void setSpeed_X(float speed_X);
    void setSpeed_Y(float speed_Y);
    void setAcceleration(float acceleration);
    void setReverse(bool isReverse);
    void setIsJumping(bool isJumping);
    void setIsShooting(bool isShooting);
    void setIsPowerup(bool isPowerup);
    void setIsBig(bool isBig);

    void accelerate(float deltaTime);

    void update(float deltaTime, 
                int window_X, 
                int window_Y);

    void loadPlayerAssets();
    Entity getLaser();
};

#endif //SIMPLEGAME_ENTITY_H
