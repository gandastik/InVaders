#include "stdafx.h"
#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f position)
{
	body.setPosition(position);
	body.setTexture(*texture);
	body.setScale(1.f, 1.f);
}

Platform::~Platform()
{

}

Collider Platform::getCollider()
{
	return Collider(body);
}

void Platform::render(sf::RenderTarget* target)
{
	target->draw(body);
}

sf::Sprite Platform::getSprite()
{
	return this->body;
}
