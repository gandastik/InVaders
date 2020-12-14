#pragma once

#include "stdafx.h"
#include "Bullet.h"
#include "Collider.h"
#include "Player.h"
#include "AnimationComponent.h"

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape body;
	std::string type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float dropChance;
	bool isDrop;
	bool isShooting;
	bool isDeath;

	bool onGround;
	bool isFaceLeft;

	//Physics
	sf::Vector2f velocity;
	float maxVelocityX;
	float maxVelocityY;
	float speedValue;
	float gravity;
	float drag;

	//Animations
	AnimationComponent* animationComponent;

	//Hitbox
	Hitbox* hitbox;

	sf::Clock takeDmgTimer;

	sf::Vector2f initPos;

	//Bullets
	std::vector<Bullet*> bullets;
	sf::Texture bulletTexture;
	sf::Texture BossBulletTexture;
	sf::Texture sniperBulletTexture;
	sf::Clock shootTimer;
	float bulletSpeed;
	float shootCooldown;
	float shootCooldownMax;

	//Resources
	sf::SoundBuffer gunshot;
	sf::Sound gunShotSound;
	sf::SoundBuffer takeDmgsfx;
	sf::Sound takeDmgSound;


	void initVariables();
	void initPhysics();
	void initSoundEffects();
	void initSprite();
	void initAnimationComponent();

public:
	//Constructure & Destructure
	Enemy(sf::Texture* texture, std::string type, float pos_x, float pos_y );
	~Enemy();

	//Accessors
	int getHp();
	int& getPoint();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	bool getIsDrop();
	bool getIsDeath();
	std::string getType();
	int getMaxHp();

	//Modifiers
	void takeDmg(int dmg);
	void setPosition(float pos_x, float pos_y);
	void resetVelocityY();
	void setOnGround();

	//Components
	void createAnimationComponent();

	//Functions
	void deathAnimation(const float& dt);
	void randomItem();
	void updateShooting(Player* player);
	Collider getCollider();
	void updatePhysics(const float& dt);
	void updateMovement(Player* player, const float& dt);
	void updateHitbox();
	void updateAnimation(const float& dt);
	void updateColor();
	void updateBullet();
	void bulletCollision(Player* player);
	void update(Player* player, const float& dt);
	void render(sf::RenderTarget* target);
};

