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

	this->bulletTexture.loadFromFile("Texture/flipped_bullet.png");
	this->shootCooldownMax = 0.75f; //in seconds
	this->shootCooldown = this->shootCooldownMax;
}

void Enemy::initSoundEffects()
{
	if(!this->gunshot.loadFromFile("Resources/Sound Effects/gun1.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS GUN" << std::endl;
	}
	this->gunShotSound.setBuffer(this->gunshot);
	this->gunShotSound.setVolume(15.f);

	if(!this->takeDmgsfx.loadFromFile("Resources/Sound Effects/enemy_take_dmg.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS ENEMY TAKE DMG" << std::endl;
	}
	this->takeDmgSound.setBuffer(this->takeDmgsfx);
	this->takeDmgSound.setVolume(10.f);
}

void Enemy::initSprite()
{
	this->currentFrame = sf::IntRect(0, 0, 42, 37);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.5f, 2.5f);
}

Enemy::Enemy(sf::Texture* texture, float pos_x, float pos_y)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	
	this->initPos.x = pos_x;
	this->initPos.y = pos_y;

	this->initVariables();
	this->initSprite();
	this->initSoundEffects();
	this->randomItem();
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

void Enemy::deathAnimation()
{
	this->currentFrame = sf::IntRect(0, 44, 30, 37);
	this->currentFrame.top = 44;
	this->currentFrame.width = 30;
	this->currentFrame.height = 37;
	for (int i = 0; i < 13; i++)
	{
		this->currentFrame.left += 30;
		this->sprite.setTextureRect(this->currentFrame);
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
void Enemy::move(Player* player)
{
	/*if (this->moveLeft)
		this->sprite.move(-1.f, 0.f);
	else this->sprite.move(1.f, 0.f);

	if (this->sprite.getPosition().x == this->initPos.x - 100.f)
		this->moveLeft = false;
	else if (this->sprite.getPosition().x == this->initPos.x + 100.f)
		this->moveLeft = true;*/

	if (this->sprite.getPosition().x - player->getPosition().x <= 1000.f && this->sprite.getPosition().x - player->getPosition().x >= 600.f)
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

	//When to shoot
	if (this->sprite.getPosition().x - player->getPosition().x <= 700.f && this->shootCooldown > this->shootCooldownMax && this->hp > 0)
	{
		std::cout << "BANG!!!" << std::endl;
		this->shoot();
		this->gunShotSound.play();
		this->shootTimer.restart();
	}
	this->move(player);
	this->updateBullet();
	this->updateColor();
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
