#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animationState = IDLE;
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
}

void Player::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 20.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.3f;
	this->drag = 0.87f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

Player::~Player()
{

}

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

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::restAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Accelearation
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.y += dir_y * this->acceleration; Gravity

	//Limit Velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;
		
	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animationState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //LEFT
	{
		this->move(-1.f, 0.f);
		this->animationState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //RIGHT
	{
		this->move(1.f, 0.f);
		this->animationState = MOVING_RIGHT;
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //TOP
	//{
	//	this->sprite.move(0.f, -3.f);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //DOWN
	//{
	//	this->sprite.move(0.f, 3.f);
	//}
}

void Player::updateAnimation()
{
	if (this->animationState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.width = 30.f;
			this->currentFrame.height = 38.f;
			this->currentFrame.left += 30.f;
			if (this->currentFrame.left >= 90.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 44.f;
			this->currentFrame.width = 40.f;
			this->currentFrame.height = 40.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 320.f)
			{
				this->currentFrame.left = 40.f;
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
			this->currentFrame.top = 44.f;
			this->currentFrame.width = 40.f;
			this->currentFrame.height = 40.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 320.f)
			{
				this->currentFrame.left = 40.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-2.5f, 2.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.5f, 0.f);
	}
	else
	{
		this->animationTimer.restart();
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
