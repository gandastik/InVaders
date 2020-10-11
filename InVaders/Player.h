#pragma once

#include "stdafx.h"

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
	bool animationSwitch;


	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Initializations
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();

public:
	//Constructors / Destructors
	Player();
	virtual ~Player();

	//Accessors
	const bool& getAnimationSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Functions
	void restAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

