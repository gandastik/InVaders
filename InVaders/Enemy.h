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

	sf::Vector2f initPos;
	bool moveLeft;

	//Bullets
	std::vector<Bullet*> bullets;
	sf::Texture bulletTexture;
	sf::Clock shootTimer;
	float shootCooldown;
	float shootCooldownMax;

	//Resources
	sf::SoundBuffer gunshot;
	sf::Sound gunShotSound;

	void initVariables();
	void initSoundEffects();
	void initSprite();

public:
	//Constructure & Destructure
	Enemy(sf::Texture* texture, float pos_x, float pos_y );
	~Enemy();

	//Accessors
	int getHp();

	//Modifiers
	void takeDmg(int dmg);
	void setPosition(float pos_x, float pos_y);

	//Functions
	void move(Player* player);
	void shoot();
	Collider getCollider();
	void updateBullet();
	void bulletCollision(Player* player);
	void update(Player* player);
	void render(sf::RenderTarget* target);
};

