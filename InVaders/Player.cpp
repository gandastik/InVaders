#include "stdafx.h"
#include "Player.h"

//Initialize Functions
void Player::initVariables()
{
	this->animationState = IDLE;
	this->hp = 10.f;
	this->isShooting = false;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerTextureSheet.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setScale(2.5f, 2.5f);
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
	this->takeDmgSound.setVolume(30.f);
}

void Player::initPhysics()
{
	this->velocityMax = 3000.f;
	this->velocityMin = 1.f;
	this->acceleration = 50.f;
	this->drag = 0.90f;
	this->gravity = 9800.f;
	this->velocityMaxY = 1000.f;
	this->onGround = false;
	this->isFaceRight = true;

	//Jump
	this->jumpForce = 450.f;
	this->gravityAcceleration = 9.81f;
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
	//this->initAnimation();
	this->initSoundEffects();
	this->initPhysics();
	this->initAnimationComponent();
	this->createHitbox(20.f, 0.f, 50 , 100);


	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 2, 0, 40, 40);
	this->animationComponent->addAnimation("RUN", 6.f, 1, 1, 8, 1, 40, 40);
	this->animationComponent->addAnimation("SHOOT", 3.f , 0, 2, 9, 2, 54, 40);
}

Player::~Player()
{
	delete this->animationComponent;
	delete this->hitbox;
}

//Accessors

const sf::Vector2f Player::getPosition() const
{
	if (this->hitbox)
		return this->hitbox->getPosition();
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Sprite& Player::getSprite() const
{
	if (this->hitbox)
		return this->hitbox->getSprite();
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
	if (this->hitbox)
		this->hitbox->setPosition(x, y);
	else
	{
		this->sprite.setPosition(x, y);
	}	
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::takeDmg(int dmg)
{
	this->sprite.setColor(sf::Color(255, 0, 0, 127));
	this->takeDmgSound.play();
	this->hp -= dmg;
	this->takeDmgTimer.restart();
}

void Player::heal(int x)
{
	this->hp += x;
}

void Player::creatAnimationComponent()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->textureSheet);
}

void Player::createHitbox(float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new Hitbox(this->sprite, offset_x, offset_y, width, height);
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

void Player::updateColor()
{
	if (this->takeDmgTimer.getElapsedTime().asSeconds() >= 0.15f)
	{
		this->sprite.setColor(sf::Color(255, 255, 255, 255));
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

	this->sprite.move(this->velocity * dt);
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
		if (this->shootCooldown.getElapsedTime().asSeconds() >= 0.4f)
		{
			this->animationState = SHOOTING;
			this->isShooting = true;
			this->gunshotSound.play();
			this->shootCooldown.restart();
		}
		
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
	if (this->animationState == MOVING_RIGHT)
	{
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setOrigin(0.f, 0.f);
		this->animationComponent->play("RUN", dt, this->velocity.x, this->velocityMax);
		this->isFaceRight = true;
	}
	if (this->animationState == MOVING_LEFT)
	{
		this->sprite.setScale(-2.5f, 2.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.5f, 0.f);
		this->animationComponent->play("RUN", dt, this->velocity.x, this->velocityMax);
		this->isFaceRight = false;
	}
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
	this->hitbox->update();
	
	this->updateColor();
	this->updateJumpCooldown(dt);
	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	
	//this->hitbox->render(*target);
}
