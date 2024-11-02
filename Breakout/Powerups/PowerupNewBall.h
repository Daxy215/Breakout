#pragma once

#include "PowerupBase.h"

// Forward declaration,
// to avoid circular dependence
class GameManager;

class PowerupNewBall : public PowerupBase {
public:
	PowerupNewBall(sf::RenderWindow* window, Paddle* paddle, GameManager* gameManer, Ball* ball, std::vector<Ball*>& balls);
	
	std::pair<POWERUPS, float> applyEffect() override;
	
private:
	GameManager* _gameManager;
	
	std::vector<Ball*>& _balls;
};
