#include "stdafx.h"
#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f position)
{
	sprite.setPosition(position);
	sprite.setTexture(*texture);
	sprite.setScale(1.f, 1.f);
	body.setPosition(position);
	body.setSize(sf::Vector2f(texture->getSize()));
}

Platform::Platform(sf::Vector2f position, sf::Vector2f size, std::string type)
{
	sprite.setPosition(position);
	sprite.setScale(1.f, 1.f);
	sprite.setColor(sf::Color::White);
	body.setPosition(position);
	body.setSize(size);
	body.setFillColor(sf::Color::White);
	this->type = type;
}

Platform::~Platform()
{

}

Collider Platform::getCollider()
{
	return Collider(body);
}

std::string Platform::getType()
{
	return this->type;
}

sf::RectangleShape Platform::getBody()
{
	return this->body;
}

void Platform::render(sf::RenderTarget* target)
{
	target->draw(body);
}

sf::Sprite Platform::getSprite()
{
	return this->sprite;
}
