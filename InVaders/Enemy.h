#pragma once

#include "stdafx.h"
#include "Bullet.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float dropChance;
	bool isDrop;

	//Animations
	sf::IntRect currentFrame;

	sf::Clock takeDmgTimer;

	sf::Vector2f initPos;

	//Bullets
	std::vector<Bullet*> bullets;
	sf::Texture bulletTexture;
	sf::Clock shootTimer;
	float shootCooldown;
	float shootCooldownMax;

	//Resources
	sf::SoundBuffer gunshot;
	sf::Sound gunShotSound;
	sf::SoundBuffer takeDmgsfx;
	sf::Sound takeDmgSound;

	void initVariables();
	void initSoundEffects();
	void initSprite();

public:
	//Constructure & Destructure
	Enemy(sf::Texture* texture, float pos_x, float pos_y );
	~Enemy();

	//Accessors
	int getHp();
	int& getPoint();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	bool getIsDrop();

	//Modifiers
	void takeDmg(int dmg);
	void setPosition(float pos_x, float pos_y);

	//Functions
	void deathAnimation();
	void randomItem();
	void move(Player* player);
	void shoot();
	Collider getCollider();
	void updateColor();
	void updateBullet();
	void bulletCollision(Player* player);
	void update(Player* player);
	void render(sf::RenderTarget* target);
};

