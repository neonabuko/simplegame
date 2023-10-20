#include <SFML/Graphics.hpp>
#include <random>

int main() {
    float window_X = 1100;
    float window_Y = 800;
    sf::RenderWindow window(sf::VideoMode(
            (int) window_X, (int) window_Y), "Simple Game"
            );

    sf::CircleShape player(40);
    player.setFillColor(sf::Color::Yellow);

    float playerDiameter = player.getRadius() * 2;
    float playerMax_X = (float) window_X - playerDiameter;
    float playerMax_Y = (float) window_Y - playerDiameter;

    float enemySize_X = 50;
    float enemySize_Y = 50;

    sf::RectangleShape enemy(sf::Vector2f(enemySize_X, enemySize_Y));
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition((float) window_X - 200, (float) window_Y - 200);

    sf::Clock clock;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> enemyDistribution(-0.5f, 0.5f);
    std::uniform_real_distribution<float> timeDistribution(0.0f, 1.5f);
    float generationInterval = timeDistribution(gen);
    float elapsedTime = 0.0f;
    float random_X = 0.0f;
    float random_Y = 0.0f;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Handle keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-0.07f, 0.0f); // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(0.07f, 0.0f); // Move right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move(0.0f, -0.07f); // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.move(0.0f, 0.07f); // Move down
        }

        // Border limits
        if (player.getPosition().x > playerMax_X) {
            player.setPosition(playerMax_X, player.getPosition().y);
        }
        if (player.getPosition().x < 0) {
            player.setPosition(0, player.getPosition().y);
        }
        if (player.getPosition().y > playerMax_Y) {
            player.setPosition(player.getPosition().x, playerMax_Y);
        }
        if (player.getPosition().y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }

        float playerBound_RIGHT = player.getPosition().x + player.getRadius();
        float playerBound_LEFT = player.getPosition().x - player.getRadius();
        float playerBound_DOWN = player.getPosition().y + player.getRadius();
        float playerBound_UP = player.getPosition().y - player.getRadius();

        float enemyBound_LEFT = enemy.getPosition().x - enemySize_X;
        float enemyBound_RIGHT = enemy.getPosition().x;
        float enemyBound_UP = enemy.getPosition().y - enemySize_Y;
        float enemyBound_DOWN = enemy.getPosition().y;

        elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= generationInterval) {
            random_X = enemyDistribution(gen) / 5;
            random_Y = enemyDistribution(gen) / 5;
            elapsedTime = 0.0f;
        }

        enemy.move(random_X, random_Y);

        if (enemyBound_RIGHT > (float) window_X - enemySize_X) {
            enemy.setPosition((float) window_X - enemySize_X, enemy.getPosition().y);
        }
        if (enemyBound_LEFT < 0 - enemySize_X) {
            enemy.setPosition(0, enemy.getPosition().y);
        }
        if (enemyBound_UP < 0 - enemySize_Y) {
            enemy.setPosition(enemy.getPosition().x, 0);
        }
        if (enemyBound_DOWN > (float) window_Y - enemySize_Y) {
            enemy.setPosition(enemy.getPosition().x, (float) window_Y - enemySize_Y);
        }

        if (playerBound_RIGHT > enemyBound_LEFT && playerBound_LEFT < enemyBound_RIGHT &&
            playerBound_DOWN > enemyBound_UP && playerBound_UP < enemyBound_DOWN)
        {
            player.setPosition(0, 0);
            enemy.setPosition((float) window_X - 200, (float) window_Y - 200);
        }

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}
