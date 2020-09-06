#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animationState = IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/player.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 32, 40);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.5f, 2.5f);
}

void Player::initAnimation()
{
	this->animationTimer.restart();
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

Player::~Player()
{

}

void Player::updateMovement()
{
	this->animationState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //LEFT
	{
		this->sprite.move(-3.f, 0.f);
		this->animationState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //RIGHT
	{
		this->sprite.move(3.f, 0.f);
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
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 65.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 368.f)
			{
				this->currentFrame.left = 66.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
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
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
