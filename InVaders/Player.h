#pragma once

#include "stdafx.h"
#include "Collider.h"
#include "AnimationComponent.h"
#include "Hitbox.h"

enum PLAYER_ANIMATION_STATE {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, SHOOTING, CROUCH};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Status
	int hp;
	sf::Clock takeDmgTimer;
	float takeDmgTime;

	//Event stuff (when pick up items)
	float shootCD;
	bool BonusState;
	sf::Clock shootCDTimer;
	bool isMelee;

	//Hitbox
	Hitbox* hitbox;

	//Animation
	AnimationComponent* animationComponent;
	short animationState;
	bool isFaceRight;
	sf::Clock shootAnimTimer;
	sf::Clock shootCooldown;
	bool isShooting;

	//sound effects
	sf::SoundBuffer gunshot;
	sf::Sound gunshotSound;
	sf::SoundBuffer takeDmgsfx;
	sf::Sound takeDmgSound;
	
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
	void updateJumpCooldown(const float &dt);

	//Initializations
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimationComponent();
	void initSoundEffects();
	void initPhysics();

public:
	//Constructors / Destructors
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Sprite& getSprite() const;
	short getAnimationState();
	const bool& getIsFaceRight();
	int getHp();
	const float& getShootCD() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void takeDmg(int dmg);
	void heal(int x);
	void reduceShootCD();
	void Melee();

	//Components
	void creatAnimationComponent();
	void createHitbox(float offset_x, float offset_y, float width, float height);

	//Functions
	void meleeAnimation(const float& dt);
	void onCollision(sf::Vector2f direction);
	void jump(const float& dt);
	void setOnGround(int temp);
	void setIsJumping();
	void move(const float& dt,const float dir_x, const float dir_y);
	void resetToNormal(const float& dt);
	void updatePhysics(const float& dt);
	void updateMovement(const float& dt);
	void updateAnimation(const float &dt);
	Collider getCollider();
	void update(const float& dt);
	//Render
	void render(sf::RenderTarget* target);
};

