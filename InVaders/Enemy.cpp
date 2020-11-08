#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->type = 0;
	this->hpMax = 3;
	this->hp = hpMax;
	this->damage = 1;
	this->points = 5;
	this->moveLeft = true;


	this->bulletTexture.loadFromFile("Texture/flipped_bullet.png");
	this->shootCooldownMax = 0.5f; //in seconds
	this->shootCooldown = this->shootCooldownMax;
}

void Enemy::initSoundEffects()
{
	if(!this->gunshot.loadFromFile("Resources/Sound Effects/gun1.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS GUN" << std::endl;
	}
	this->gunShotSound.setBuffer(gunshot);
	this->gunShotSound.setVolume(15.f);
}

void Enemy::initSprite()
{

}

Enemy::Enemy(sf::Texture* texture, float pos_x, float pos_y)
{
	this->initVariables();
	this->initSprite();
	this->initSoundEffects();

	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(2.5f, 2.5f);

	this->initPos.x = pos_x;
	this->initPos.y = pos_y;
}

Enemy::~Enemy()
{
	//delete bullets
	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
}

//Accessors
int Enemy::getHp()
{
	return this->hp;
}

//Modifiers
void Enemy::takeDmg(int dmg)
{
	this->hp -= dmg;
}

void Enemy::setPosition(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}

//Functions
void Enemy::move(Player* player)
{
	/*if (this->moveLeft)
		this->sprite.move(-1.f, 0.f);
	else this->sprite.move(1.f, 0.f);

	if (this->sprite.getPosition().x == this->initPos.x - 100.f)
		this->moveLeft = false;
	else if (this->sprite.getPosition().x == this->initPos.x + 100.f)
		this->moveLeft = true;*/

	if (this->sprite.getPosition().x - player->getPosition().x <= 600.f && this->sprite.getPosition().x - player->getPosition().x >= 150.f)
	{
		this->sprite.move(-1.f, 0.f);
	}

}

void Enemy::shoot()
{
	this->bullets.push_back(new Bullet(&this->bulletTexture, this->sprite.getPosition().x,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.f - 5.f, -1.f, 0.f, 5.f));
}

Collider Enemy::getCollider()
{
	return Collider(this->sprite);
}

void Enemy::updateBullet()
{
	for (auto* bullet : this->bullets)
	{
		bullet->update();
	}
}

void Enemy::bulletCollision(Player* player)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		//bullet culling (right screen)
		if (bullet->getBounds().left < 0.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//Bullet collide with player
		/*if (Collision::BoundingBoxTest(playerSprite , bullet->getSprite()))
		{
			std::cout << "HIT!!" << std::endl;
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}*/
		//Bullet collide with player
		if (bullet->isIntersects(player->getSprite().getGlobalBounds()))
		{
			std::cout << "HIT!!" << std::endl;
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			
			//Decrease player hp
			player->takeDmg(1);
			std::cout << player->getHp() << std::endl;
		}
	}
	counter++;
}

//Functions
void Enemy::update(Player* player)
{
	this->shootCooldown = this->shootTimer.getElapsedTime().asSeconds();

	if (this->sprite.getPosition().x - player->getPosition().x <= 500.f && this->shootCooldown > this->shootCooldownMax)
	{
		std::cout << "BANG!!!" << std::endl;
		this->shoot();
		this->gunShotSound.play();
		this->shootTimer.restart();
	}

	this->move(player);
	this->updateBullet();
	this->bulletCollision(player);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	
	for (auto* bullet : this->bullets)
	{
		bullet->render(target);
	}
}
