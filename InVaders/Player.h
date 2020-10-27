#pragma once

#include "stdafx.h"

enum PLAYER_ANIMATION_STATE {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, SHOOTING};

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
	sf::IntRect idleCurrentFrame;
	sf::IntRect shootingCurrentFrame;

	bool isFaceRight;
	

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;
	bool onGround;
	
	//Jump Mechanic
	float jumpForce;
	float gravityAcceleration;
	float speedValue;
	float mass;
	bool isJumping;
	const bool canJump();
	float jumpCooldown;
	float jumpCooldownMax;
	void updateJumpCooldown();
	
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
	sf::Sprite getSprite();
	short getAnimationState();
	const bool& getIsFaceRight();

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Functions
	void jump(const float& dt);
	void setOnGround();
	void restAnimationTimer();
	void move(const float& dt,const float dir_x, const float dir_y);
	void updatePhysics(const float& dt);
	void updateMovement(const float& dt);
	void updateAnimation();
	void resetAnimationState();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

