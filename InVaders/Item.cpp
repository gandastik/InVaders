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
		
}

Item::~Item()
{
	delete this->animationComponent;
}

sf::FloatRect Item::getGlobalBounds()
{
	if(this->type == "HEAL")
		return this->hitbox->getGlobalBounds();
	return this->shape.getGlobalBounds();
}

const std::string& Item::getType() const
{
	return this->type;
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
	if(this->type == "HEAL")
		this->animationComponent->play("IDLE", dt);
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
	
	/*if(this->type == "HEAL")
		this->hitbox->render(*target);*/
}
