#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "PowerupBase.h"
#include "../Paddle.h"
#include "../Ball.h"

// Forward declaration,
// to avoid circular dependence
class GameManager;

class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, GameManager* gameManager, std::vector<Ball*>& balls);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    sf::RenderWindow* _window;
    Paddle* _paddle;

    GameManager* _gameManager;
    
    // This is referenced from,
    // the GameManager clas
    std::vector<Ball*>& _balls;
    std::vector<PowerupBase*> _powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.
};
