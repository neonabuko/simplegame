#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Assets {
    namespace Textures {
        sf::Texture background;
        sf::Texture backgroundRed;
        sf::Texture enemy;
        sf::Texture enemy_reverse;
        sf::Texture heart;
        sf::Texture laserRed;
        sf::Texture laserRed_reverse;
        sf::Texture laserBlue;
        sf::Texture laserBlue_reverse;
        sf::Texture player;
        sf::Texture player_reverse;
        sf::Texture explosion;
        sf::Texture explosion_opaque50;
    }

    namespace Sounds {
        sf::SoundBuffer explosion;
        sf::SoundBuffer gameover;
        sf::SoundBuffer hurt;
        sf::SoundBuffer jump;
        sf::SoundBuffer laserShoot;
        sf::SoundBuffer laserShootBig;
        sf::SoundBuffer pop;
        sf::SoundBuffer shrink_ray;
        sf::SoundBuffer stomp;
    }
    
    void loadTextures() {
        Textures::background.loadFromFile("../src/assets/icon/background.jpg");
        Textures::backgroundRed.loadFromFile("../src/assets/icon/backgroundRed.jpg");
        Textures::heart.loadFromFile("../src/assets/icon/heart.png");
        Textures::laserRed.loadFromFile("../src/assets/icon/laser.png");
        Textures::laserRed_reverse.loadFromFile("../src/assets/icon/laser_reverse.png");
        Textures::laserBlue.loadFromFile("../src/assets/icon/laserBlue.png");
        Textures::laserBlue_reverse.loadFromFile("../src/assets/icon/laserBlue_reverse.png");
        Textures::enemy.loadFromFile("../src/assets/icon/enemy.png");
        Textures::enemy_reverse.loadFromFile("../src/assets/icon/enemy_reverse.png");
        Textures::player.loadFromFile("../src/assets/icon/player.png");
        Textures::player_reverse.loadFromFile("../src/assets/icon/player_reverse.png");
        Textures::explosion.loadFromFile("../src/assets/icon/explosion.png");
        Textures::explosion_opaque50.loadFromFile("../src/assets/icon/explosion_opaque50.png");
    }

    void loadSounds() {
        Sounds::explosion.loadFromFile("../src/assets/sound/explosion.ogg");
        Sounds::gameover.loadFromFile("../src/assets/sound/gameover.ogg");
        Sounds::hurt.loadFromFile("../src/assets/sound/hurt.ogg");
        Sounds::jump.loadFromFile("../src/assets/sound/jump.ogg");
        Sounds::laserShoot.loadFromFile("../src/assets/sound/laserShoot.ogg");
        Sounds::laserShootBig.loadFromFile("../src/assets/sound/laserShootBig.ogg");
        Sounds::pop.loadFromFile("../src/assets/sound/pop.ogg");
        Sounds::shrink_ray.loadFromFile("../src/assets/sound/shrink_ray.ogg");
        Sounds::stomp.loadFromFile("../src/assets/sound/stomp.ogg");
    }
}
    