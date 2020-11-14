#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->type = 0;
	this->hpMax = 3;
	this->hp = hpMax;
	this->damage = 1;
	this->points = 5;
	this->dropChance = 50;
	this->isDeath = false;

	this->bulletTexture.loadFromFile("Texture/flipped_bullet.png");
	this->shootCooldownMax = 1.f; //in seconds
	this->shootCooldown = this->shootCooldownMax;
}

void Enemy::initPhysics()
{
	this->maxVelocityX = 200.f;
	this->maxVelocityY = 1000.f;
	this->speedValue = 50.f;
	this->gravity = 1500.f;
	this->drag = 0.95f;
}

void Enemy::initSoundEffects()
{
	if (!this->gunshot.loadFromFile("Resources/Sound Effects/gun1.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS GUN" << std::endl;
	}
	this->gunShotSound.setBuffer(this->gunshot);
	this->gunShotSound.setVolume(15.f);

	if (!this->takeDmgsfx.loadFromFile("Resources/Sound Effects/enemy_take_dmg.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS ENEMY TAKE DMG" << std::endl;
	}
	this->takeDmgSound.setBuffer(this->takeDmgsfx);
	this->takeDmgSound.setVolume(10.f);
}

void Enemy::initSprite()
{
	this->sprite.setScale(2.5f, 2.5f);
}

void Enemy::initAnimationComponent()
{
	this->createAnimationComponent();
}

Enemy::Enemy(sf::Texture* texture, float pos_x, float pos_y)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->texture = *texture;

	this->initPos.x = pos_x;
	this->initPos.y = pos_y;

	this->initVariables();
	this->initPhysics();
	this->initSprite();
	this->initSoundEffects();
	this->initAnimationComponent();
	this->randomItem();

	//Add animations
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 0, 0, 42, 40);
	this->animationComponent->addAnimation("DEATH", 5.f, 0, 1, 10, 1, 30, 40);
	this->animationComponent->addAnimation("SHOOTING", 7.f, 0, 2, 4, 2, 61, 40);

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

int& Enemy::getPoint()
{
	return this->points;
}

sf::Vector2f Enemy::getPosition()
{
	return this->sprite.getPosition();
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

bool Enemy::getIsDrop()
{
	return this->isDrop;
}

bool Enemy::getIsDeath()
{
	return this->isDeath;
}

//Modifiers
void Enemy::takeDmg(int dmg)
{
	this->sprite.setColor(sf::Color(255, 0, 0, 127));
	this->takeDmgSound.play();
	this->hp -= dmg;
	this->takeDmgTimer.restart();
}

void Enemy::setPosition(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}

void Enemy::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Enemy::createAnimationComponent()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->texture);
}

void Enemy::deathAnimation(const float& dt)
{
	if (this->hp <= 0)
	{
		if (this->animationComponent->play("DEATH", dt, true))
		{
			this->isDeath = true;
		}
	}
}

void Enemy::randomItem()
{
	if (rand() % 100 <= this->dropChance)
	{
		this->isDrop = true;
	}
	else this->isDrop = false;
}

//Functions
void Enemy::shoot()
{
	this->isShooting = true;
	this->bullets.push_back(new Bullet(&this->bulletTexture, this->sprite.getPosition().x,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.f - 5.f, -1.f, 0.f, 5.f));
}

Collider Enemy::getCollider()
{
	return Collider(this->sprite);
}

void Enemy::updatePhysics(const float& dt)
{
	this->velocity.y += this->gravity * dt;

	this->velocity *= this->drag;

	if (abs(this->velocity.y) > this->maxVelocityY)
	{
		if (this->velocity.y > 0) this->velocity.y = this->maxVelocityY;
		else this->velocity.y = -this->maxVelocityY;
	}
	if (abs(this->velocity.x) > this->maxVelocityX)
	{
		if (this->velocity.x > 0) this->velocity.x = this->maxVelocityX;
		else this->velocity.x = -this->maxVelocityX;
	}

	//Limit min Velocity
	if (std::abs(this->velocity.x) < 3.f)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < 3.f)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity * dt);
}

void Enemy::updateMovement(Player* player, const float& dt)
{
	if (this->sprite.getPosition().x - player->getPosition().x <= 1000.f && this->sprite.getPosition().x - player->getPosition().x >= 600.f)
	{
		this->velocity.x -= this->speedValue;
	}

}

void Enemy::updateAnimation(const float& dt)
{
	if (this->isShooting)
	{
		if (this->animationComponent->play("SHOOTING", dt, true))
		{
			this->isShooting = false;
		}
	}
	else this->animationComponent->play("IDLE", dt);
}

void Enemy::updateColor()
{
	if (this->takeDmgTimer.getElapsedTime().asSeconds() >= 0.15f)
	{
		this->sprite.setColor(sf::Color(255, 255, 255, 255));
	}
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
		//bullet culling (left screen)
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
			//Decrease player hp
			player->takeDmg(1);
			std::cout << player->getHp() << std::endl;

			--counter;
		}
	}
	counter++;
}

//Functions
void Enemy::update(Player* player, const float& dt)
{
	this->shootCooldown = this->shootTimer.getElapsedTime().asSeconds();

	//When to shoot
	if (this->sprite.getPosition().x - player->getPosition().x <= 700.f && this->shootCooldown > this->shootCooldownMax && this->hp > 0)
	{
		std::cout << "BANG!!!" << std::endl;
		this->shoot();
		this->gunShotSound.play();
		this->shootTimer.restart();
	}

	this->updateMovement(player, dt);
	this->updatePhysics(dt);
	this->updateBullet();
	this->updateColor();
	this->updateAnimation(dt);
	this->deathAnimation(dt);
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