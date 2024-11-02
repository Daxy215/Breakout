#include "PowerupNewBall.h"

#include "../GameManager.h"

PowerupNewBall::PowerupNewBall(sf::RenderWindow* window, Paddle* paddle, GameManager* gameManager, Ball* ball, std::vector<Ball*>& balls) 
									: PowerupBase(window, paddle, ball), _gameManager(gameManager), _balls(balls) {
	_sprite.setFillColor(newBallEffectsColour);
}

std::pair<POWERUPS, float> PowerupNewBall::applyEffect() {
	// Summon a new ball
	// For balancing, making this much slower
	_balls.push_back(new Ball(_window, 50.0f, _gameManager));
	
	// Since I want this to stay forever,
	// I'll just return a very large number
	return { newBall, 200000 };
}

