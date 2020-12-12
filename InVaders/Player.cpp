#include "stdafx.h"
#include "Player.h"

//Initialize Functions
void Player::initVariables()
{
	this->sprite = new sf::Sprite;
	this->animationState = IDLE;
	this->maxHp = 20.f;
	this->hp = maxHp;
	this->isShooting = false;
	this->shootCD = 0.4f;
	this->name = "";
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerTextureSheet.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
}

void Player::initSprite()
{
	this->sprite->setTexture(this->textureSheet);
	this->scaleX = 2.5f;
	this->scaleY = 2.5f;
	this->sprite->setScale(this->scaleX, this->scaleY);
}

void Player::initAnimationComponent()
{
	this->creatAnimationComponent();
}

void Player::initSoundEffects()
{
	if (!this->gunshot.loadFromFile("Resources/Sound Effects/gun4.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD FROM FILE GUN1" << std::endl;
	this->gunshotSound.setBuffer(gunshot);
	this->gunshotSound.setVolume(30.f);

	if (!this->takeDmgsfx.loadFromFile("Resources/Sound Effects/player_take_dmg.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD FROM FILE PLAYER_TAKE_DMG" << std::endl;
	this->takeDmgSound.setBuffer(this->takeDmgsfx);
	this->takeDmgSound.setVolume(25.f);
}

void Player::initPhysics()
{
	this->velocityMax = 3000.f;
	this->velocityMin = 1.f;
	this->acceleration = 50.f;
	this->drag = 0.90f;
	this->gravity = 7500.f;
	this->velocityMaxY = 1000.f;
	this->onGround = false;
	this->isFaceRight = true;

	//Jump
	this->jumpForce = 400.f;
	this->gravityAcceleration = 9.81f;
	this->speedValue = 0;
	this->mass = 60.f;
	this->isJumping = false;
	this->jumpCooldownMax = 30.f;
	this->jumpCooldown = this->jumpCooldownMax;
}

//Constructors / Destructors
Player::Player()
{
	this->initVariables();
	//this->sprite->setPosition(12000, 0);
	this->initTexture();
	this->initSprite();
	this->initSoundEffects();
	this->initPhysics();
	this->initAnimationComponent();
	this->createHitbox(20.f, 80.f, 50 , 20);


	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 2, 0, 40, 40);
	this->animationComponent->addAnimation("RUN", 6.f, 1, 1, 8, 1, 40, 40);
	this->animationComponent->addAnimation("SHOOT", 3.f , 0, 2, 9, 2, 54, 40);
	this->animationComponent->addAnimation("MELEE", 8.f , 0, 4, 5, 4, 54, 40);
	this->animationComponent->addAnimation("JUMP", 15.f , 0, 5, 8, 5, 40, 48);
}

Player::~Player()
{
	delete this->animationComponent;
	delete this->hitbox;
}

//Accessors

const sf::Vector2f Player::getPosition() const
{
	return this->sprite->getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite->getGlobalBounds();
}

sf::Sprite& Player::getSprite()
{
	return *this->sprite;
}

short Player::getAnimationState()
{
	return this->animationState;
}

const bool& Player::getIsFaceRight()
{
	return this->isFaceRight;
}

int Player::getHp()
{
	return this->hp;
}

const int& Player::getMaxHp() const
{
	return this->maxHp;
}

const float& Player::getShootCD() const
{
	return this->shootCD;
}

const bool Player::canJump()
{
	if (this->jumpCooldown >= this->jumpCooldownMax)
	{
		this->jumpCooldown = 0.f;
		return true;
	}
	return false;
}

const bool& Player::getBonusState() const
{
	return this->BonusState;
}

const int& Player::getScore() const
{
	return this->score;
}
std::string Player::getName()
{
	return this->name;
}

const bool& Player::getIsShooting() const
{
	return this->isShooting;
}

const bool& Player::getIsJump() const
{
	return this->isJump;
}

//Modifiers
void Player::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;
	this->sprite->setScale(x, y);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite->setPosition(x, y);	
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::takeDmg(int dmg)
{
	this->sprite->setColor(sf::Color(255, 0, 0, 127));
	this->takeDmgSound.play();
	this->hp -= dmg;
	this->takeDmgTimer.restart();
}

void Player::heal(int x)
{
	this->hp += x;
}

void Player::reduceShootCD()
{
	this->animationComponent->addAnimation("SHOOT", 1.f, 0, 2, 9, 2, 54, 40);
	this->shootCD = 0.2f;
	this->BonusState = true;
	this->shootCDTimer.restart();
}

void Player::Melee()
{
	this->isMelee = true;
}

void Player::addScore(int x)
{
	this->score += x;
}

void Player::setName(std::string name)
{
	this->name.assign(name);
}

void Player::creatAnimationComponent()
{
	this->animationComponent = new AnimationComponent(*this->sprite, this->textureSheet);
}

void Player::createHitbox(float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new Hitbox(*this->sprite, offset_x, offset_y, width, height);
}

void Player::setOnGround(int temp)
{
	if (temp == 1)
	{
		this->onGround = true;
	}
	else this->onGround = false;
}

void Player::setIsJumping()
{
	this->isJumping = false;
}

void Player::setJumpForce(float x)
{
	this->jumpForce = x;
}

void Player::setHP(int x)
{
	this->hp = x;
}

//Functions

void Player::move(const float& dt, const float dir_x, const float dir_y)
{
	//Accelearation
	this->velocity.x += dir_x * this->acceleration;
	//Limit Max Velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1.f : 1.f);
	}
}

void Player::resetToNormal(const float& dt)
{
	if (this->takeDmgTimer.getElapsedTime().asSeconds() >= 0.15f)
	{
		this->sprite->setColor(sf::Color(255, 255, 255, 255));
	}

	if (this->shootCDTimer.getElapsedTime().asSeconds() >= 5.f && this->BonusState)
	{
		if (!isShooting)
		{
			this->animationComponent->addAnimation("SHOOT", 3.f, 0, 2, 9, 2, 54, 40);
			this->shootCD = 0.4f;
			this->BonusState = false;
		}
	}
}

void Player::meleeAnimation(const float& dt)
{
	if (isMelee)
	{
		if (this->animationComponent->play("MELEE", dt, true))
			this->isMelee = false;
	}
}

void Player::onCollision(sf::Vector2f direction, float dt)
{
	if (direction.x < 0.f)
	{
		//Collision on the left
		this->velocity.x = 0.f;
	}
	else if(direction.x > 0.f)
	{
		//Collision on the right
		this->velocity.x = 0.f;
	}
	if (direction.y < 0.f)
	{
		//Collision on the bottom
		this->onGround = true;
		this->isJumping = false;
	}
	else if (direction.y > 0.f)
	{
		//Collision on the top
		this->velocity.y = 0.f;
	}
}

void Player::jump(const float& dt)
{
	this->speedValue -= this->gravityAcceleration * dt;
	this->sprite->move(0, -speedValue);
}



void Player::updateJumpCooldown(const float &dt)
{
	if (this->jumpCooldown < this->jumpCooldownMax)
	{
		this->jumpCooldown += 50.f * dt;
	}
}

void Player::updatePhysics(const float& dt)
{
	//Gravity
	if(!this->onGround)
		this->velocity.y += 1.0 * this->gravity * dt;

	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		if (this->velocity.y > 0.f) this->velocity.y = this->velocityMaxY;
		if (this->velocity.y < 0.f) this->velocity.y = -this->velocityMaxY;
	}

	//Deceleration
	this->velocity *= this->drag;
	
	//Limit min Velocity
	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}
	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
	//std::cout << "Y velocity = " << this->velocity.y << " " << this->speedValue << "\n";
	//std::cout << dt << "\n";
	
	if (this->isJumping) {
		this->jump(dt);
	}

	this->sprite->move(this->velocity * dt);
}

void Player::updateMovement(const float& dt)
{
	this->animationState = IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //LEFT
	{
		this->move(dt, -1.f, 0.f);
		this->animationState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //RIGHT
	{
		this->move(dt, 1.f, 0.f);
		this->animationState = MOVING_RIGHT;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->isJumping == false && canJump() && !this->isShooting && !this->isMelee) //JUMP
	{
		//this->move(dt, 0.f, -1.f);
		//this->onGround = false;
		//this->animationState = JUMPING;
		this->speedValue = this->jumpForce / this->mass;
		this->isJumping = true;
		this->isJump = true;
	}
	
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //DOWN
	//{
	//	this->sprite.move(0.f, 3.f);
	//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !this->isJump)
	{
		if (this->shootCooldown.getElapsedTime().asSeconds() >= this->shootCD)
		{
			this->animationState = SHOOTING;
			this->isShooting = true;
			this->gunshotSound.play();
			this->shootCooldown.restart();
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
	{
		this->sprite->setPosition(12000.f, 0.f);
	}
}

void Player::updateAnimation(const float &dt)
{
	if (this->animationState == IDLE)
	{
		this->animationComponent->play("IDLE", dt);
	}
	if (this->isShooting)
	{
		if (this->animationComponent->play("SHOOT", dt, true))
			this->isShooting = false;
	}
	if (this->isMelee)
	{
		if (this->animationComponent->play("MELEE", dt, true))
			this->isMelee = false;
	}
	if (this->isJump)
	{
		if (this->animationComponent->play("JUMP", dt, true))
			this->isJump = false;
	}
	if (this->animationState == MOVING_RIGHT)
	{
		this->sprite->setScale(this->scaleX, this->scaleY);
		this->sprite->setOrigin(0.f, 0.f);
		this->animationComponent->play("RUN", dt, this->velocity.x, this->velocityMax);
		this->isFaceRight = true;
	}
	if (this->animationState == MOVING_LEFT)
	{
		this->sprite->setScale(-this->scaleX, this->scaleY);
		this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2.5f, 0.f);
		this->animationComponent->play("RUN", dt, this->velocity.x, this->velocityMax);
		this->isFaceRight = false;
	}
}

Collider Player::getCollider()
{
	return Collider(this->hitbox->getHitbox());
}

void Player::update(const float& dt)
{
	this->updateMovement(dt);
	this->updatePhysics(dt);
	this->updateAnimation(dt);
	this->hitbox->update();
	
	this->resetToNormal(dt);
	this->updateJumpCooldown(dt);
	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
	
	//this->hitbox->render(*target);
}
