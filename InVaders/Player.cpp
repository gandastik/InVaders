#include "stdafx.h"
#include "Player.h"

//Initialize Functions
void Player::initVariables()
{
	this->animationState = IDLE;
	this->hp = 10.f;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerAnimation.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 0, 0);
	
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.5f, 2.5f);

	//Idle
	this->idleCurrentFrame = sf::IntRect(0, 0, 30, 38);

	//Shooting
	this->shootingCurrentFrame = sf::IntRect(0, 0, 54, 37);
}

void Player::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initSoundEffects()
{
	if (!this->gunshot.loadFromFile("Resources/Sound Effects/gun4.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD FROM FILE GUN1" << std::endl;
	this->gunshotSound.setBuffer(gunshot);
	this->gunshotSound.setVolume(30.f);
}

void Player::initPhysics()
{
	this->velocityMax = 3000.f;
	this->velocityMin = 1.f;
	this->acceleration = 60.f;
	this->drag = 0.90f;
	this->gravity = 55.f;
	this->velocityMaxY = 1000.f;
	this->onGround = false;
	this->isFaceRight = true;

	//Jump
	this->jumpForce = 450.f;
	this->gravityAcceleration = 9.8f;
	this->speedValue = 0;
	this->mass = 65.f;
	this->isJumping = false;
	this->jumpCooldownMax = 45.f;
	this->jumpCooldown = this->jumpCooldownMax;
}

//Constructors / Destructors
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initSoundEffects();
	this->initPhysics();
}

Player::~Player()
{

}

//Accessors
const bool& Player::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}
	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::Sprite Player::getSprite()
{
	return this->sprite;
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

const bool Player::canJump()
{
	if (this->jumpCooldown >= this->jumpCooldownMax)
	{
		this->jumpCooldown = 0.f;
		return true;
	}
	return false;
}

//Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::takeDmg(int dmg)
{
	this->hp -= dmg;
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

//Functions
void Player::restAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

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

void Player::onCollision(sf::Vector2f direction)
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
	}
}

void Player::jump(const float& dt)
{
	this->speedValue -= this->gravityAcceleration * dt;
	this->sprite.move(0, -speedValue);
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
		this->velocity.y += 1.0 * this->gravity;

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

	this->sprite.move(this->velocity * dt);
}

void Player::updateMovement(const float& dt)
{
	this->animationState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //LEFT
	{
		this->move(dt, -1.f, 0.f);
		this->animationState = MOVING_LEFT;
		this->isFaceRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //RIGHT
	{
		this->move(dt, 1.f, 0.f);
		this->animationState = MOVING_RIGHT;
		this->isFaceRight = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //CROUCH
	{
		this->animationState = CROUCH;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->isJumping == false && canJump()) //JUMP
	{
		//this->move(dt, 0.f, -1.f);
		//this->onGround = false;
		//this->animationState = JUMPING;
		this->speedValue = this->jumpForce / this->mass;
		this->isJumping = true;
	}
	
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //DOWN
	//{
	//	this->sprite.move(0.f, 3.f);
	//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->shootCooldown.getElapsedTime().asSeconds() >= 0.25f)
		{
			this->animationState = SHOOTING;
			this->gunshotSound.play();
			this->shootCooldown.restart();
		}
		
	}
}

void Player::updateAnimation(const float &dt)
{
	if (this->animationState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimationSwitch())
		{
			this->idleCurrentFrame.top = 0;
			this->idleCurrentFrame.width = 30;
			this->idleCurrentFrame.height = 38;
			this->idleCurrentFrame.left += 30;
			if (this->idleCurrentFrame.left >= 90)
			{
				this->idleCurrentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->idleCurrentFrame);
		}
	}
	else if (this->animationState == MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 42;
			this->currentFrame.width = 39;
			this->currentFrame.height = 39;
			this->currentFrame.left += 39;
			if (this->currentFrame.left >= 312)
			{
				this->currentFrame.left = 39;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animationState == MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 42;
			this->currentFrame.width = 39;
			this->currentFrame.height = 39;
			this->currentFrame.left += 39;
			if (this->currentFrame.left >= 312)
			{
				this->currentFrame.left = 39;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-2.5f, 2.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.5f, 0.f);
	}
	else if (this->animationState == SHOOTING )
	{
		/*if (this->animationTimer.getElapsedTime().asSeconds() >= 0.01f || this->getAnimationSwitch())
		{*/
			this->shootingCurrentFrame.top = 100;
			this->shootingCurrentFrame.width = 54;
			this->shootingCurrentFrame.height = 37;
			for (float i = 0; i < 10; i ++)
			{
				this->shootingCurrentFrame.left += 54;
				if (this->shootingCurrentFrame.left >= 215)
				{
					this->shootingCurrentFrame.left = 0;
					this->shootingCurrentFrame.top = 147;
				}
				this->sprite.setTextureRect(this->shootingCurrentFrame);
			}
		/*}			
		this->animationTimer.restart();*/
	}

	else
	{
		this->animationTimer.restart();
	}
}

void Player::resetAnimationState()
{
	this->animationState = IDLE;
}

Collider Player::getCollider()
{
	return Collider(this->sprite);
}

void Player::update(const float& dt)
{
	this->updateMovement(dt);
	this->updatePhysics(dt);
	this->updateAnimation(dt);
	this->updateJumpCooldown(dt);

	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
