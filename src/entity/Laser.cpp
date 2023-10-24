#include <SFML/Graphics.hpp>
#include <vector>

class Laser {
public:
    Laser(float startX, float startY, float velocity) {
        sf::Texture laserTexture;
        laserTexture.loadFromFile("../src/assets/icon/laser.png");
        laser.setTexture(laserTexture);
        laser.setScale(sf::Vector2f(5, 20));
        laser.setPosition(startX, startY);
        this->velocity = velocity;
    }

    void update() {
        laser.move(velocity, 0);
    }

    sf::Sprite laser;
private:
    float velocity;
};