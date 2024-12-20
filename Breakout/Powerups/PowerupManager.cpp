#include "PowerupManager.h"

#include "PowerupBigPaddle.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupNewBall.h"
#include "PowerupSlowBall.h"
#include "PowerupSmallPaddle.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, GameManager* gameManager, std::vector<Ball*>& balls)
    : _window(window), _paddle(paddle), _gameManager(gameManager), _balls(balls)
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{
    // Apply the power up,
    // to a random ball
    Ball* ball = _balls[rand() % _balls.size()];
    
    // TODO finish this.
    switch (rand() % 6)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, ball));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, ball));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, ball));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, ball));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, ball));
        break;
    case 5:
        _powerups.push_back(new PowerupNewBall(_window, _paddle, _gameManager, ball, _balls));
       break;
    }
}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
