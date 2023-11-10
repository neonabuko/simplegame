#include "../src/include/GameAssets.h"
#include "../src/include/PlayerAssets.h"
#include "../src/include/LaserAssets.h"
#include "../src/include/EnemyAssets.h"

using namespace GameAssets;
using namespace EnemyAssets;
using namespace PlayerAssets;
using namespace LaserAssets;

int main() {
    loadGameAssets();

    while (window.isOpen()) {
        updateSprites();

        if (!isGameOver) {
            player.update();
            laser.update();
            for (Enemy& enemy : enemies) enemy.update();
        }

        updateGameCommands();
        updateKeyboard();
        updateSounds();

        window.display();
    }

    return 0;
}
