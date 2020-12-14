#include "stdafx.h"
#include "Item.h"

void Item::initAnimationComponent()
{
	this->createAnimationComponent();
}

Item::Item(sf::Texture* texture, std::string type, float x, float y)
	:type(type), texture(*texture)
{
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*texture);
	
	this->initAnimationComponent();

	this->shape.setTexture(texture);
	this->shape.setSize(sf::Vector2f(texture->getSize().x * 2.f, texture->getSize().y * 2.f));
	this->shape.setPosition(x, y);

	this->sprite->setPosition(x, y);
	this->sprite->setScale(2.f, 2.f);

	if (type == "HEAL")
	{
		this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 5, 0, 28, 18);
		this->createHitbox(10, 0, 46, 36);
	}
	if (type == "BONUS")
	{
		this->animationComponent->addAnimation("IDLE", 1.f, 0, 0, 0, 0, 22, 20);
		this->createHitbox(0, 0, 44, 40);
	}
	if (type == "COIN")
	{
		this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 8, 0, 16, 16);
		this->createHitbox(0, 0, 32, 32);
	}
	if (type == "POO")
	{
		this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 5, 0, 23, 27);
		this->createHitbox(0, 0, 45, 54);
	}
	if(type == "CHICKEN")
	{
		this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 7, 0, 31, 30);
		this->createHitbox(0, 0, 62, 60);
	}
	if (type == "KEY")
	{
		this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 5, 0, 14, 21);
		this->createHitbox(0, 0, 28, 42);
	}
	if (type == "GO")
	{
		this->animationComponent->addAnimation("IDLE", 30.f, 0, 0, 3, 0, 33, 31);
		this->createHitbox(0, 0, 66, 62);
	}
}

Item::~Item()
{
	delete this->animationComponent;
	delete this->hitbox;
}

sf::FloatRect Item::getGlobalBounds()
{
	if (this->type == "HEAL")
		return this->hitbox->getGlobalBounds();
	if (this->type == "COIN")
		return this->hitbox->getGlobalBounds();
	if (this->type == "POO")
		return this->hitbox->getGlobalBounds();
	if (this->type == "CHICKEN")
		return this->hitbox->getGlobalBounds();
	if (this->type == "BONUS")
		return this->hitbox->getGlobalBounds();
	if (this->type == "KEY")
		return this->hitbox->getGlobalBounds();
	if (this->type == "GO")
		return this->hitbox->getGlobalBounds();
	return this->shape.getGlobalBounds();
}

const std::string& Item::getType() const
{
	return this->type;
}

void Item::setPosition(float x, float y)
{
	this->sprite->setPosition(x, y);
}

void Item::createAnimationComponent()
{
	this->animationComponent = new AnimationComponent(*this->sprite, this->texture);
}

void Item::createHitbox(float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new Hitbox(*this->sprite, offset_x, offset_y, width, height);
}

void Item::update(const float& dt)
{
	this->animationComponent->play("IDLE", dt);
	this->hitbox->update();
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
	
	//this->hitbox->render(*target);
}
