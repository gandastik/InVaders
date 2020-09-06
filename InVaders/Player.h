#pragma once

enum PLAYER_ANIMATION_STATE {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	short animationState;
	sf::IntRect currentFrame;

	//Movement


	//Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:
	Player();
	virtual ~Player();

	//Functions
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

