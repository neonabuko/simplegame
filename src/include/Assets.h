#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Assets {
    namespace Textures {
        sf::Texture background;
        sf::Texture enemy;
        sf::Texture enemy_reverse;
        sf::Texture heart;
        sf::Texture laser;
        sf::Texture laser_reverse;
        sf::Texture player;
        sf::Texture player_reverse;
    }

    namespace Sounds {
        sf::SoundBuffer explosion;
        sf::SoundBuffer gameover;
        sf::SoundBuffer hurt;
        sf::SoundBuffer jump;
        sf::SoundBuffer laserShoot;
        sf::SoundBuffer pop;
        sf::SoundBuffer shrink_ray;
        sf::Music soundtrack;
    }

    namespace Fonts {
        sf::Font hackNerd;
    }
    
    void loadTextures() {
        Textures::background.loadFromFile("../src/assets/icon/background.jpg");
        Textures::heart.loadFromFile("../src/assets/icon/heart.png");
        Textures::laser.loadFromFile("../src/assets/icon/laser.png");
        Textures::laser_reverse.loadFromFile("../src/assets/icon/laser_reverse.png");
        Textures::enemy.loadFromFile("../src/assets/icon/enemy.png");
        Textures::enemy_reverse.loadFromFile("../src/assets/icon/enemy_reverse.png");
        Textures::player.loadFromFile("../src/assets/icon/player.png");
        Textures::player_reverse.loadFromFile("../src/assets/icon/player_reverse.png");
    }

    void loadSounds() {
        Sounds::explosion.loadFromFile("../src/assets/sound/explosion.ogg");
        Sounds::gameover.loadFromFile("../src/assets/sound/gameover.ogg");
        Sounds::hurt.loadFromFile("../src/assets/sound/hurt.ogg");
        Sounds::jump.loadFromFile("../src/assets/sound/jump.ogg");
        Sounds::laserShoot.loadFromFile("../src/assets/sound/laserShoot.ogg");
        Sounds::pop.loadFromFile("../src/assets/sound/pop.ogg");
        Sounds::shrink_ray.loadFromFile("../src/assets/sound/shrink_ray.ogg");
        Sounds::soundtrack.openFromFile("../src/assets/sound/soundtrack.ogg");
    }

    void loadFonts() {
        Fonts::hackNerd.loadFromFile("../src/assets/font/HackNerdFont-Regular.ttf");
    }
}
    