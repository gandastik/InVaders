#include "stdafx.h"
#include "Item.h"

Item::Item(sf::Texture* texture, float x, float y)
{
	this->shape.setTexture(texture);
	this->shape.setSize(sf::Vector2f(texture->getSize().x * 2.f, texture->getSize().y * 2.f));
	this->shape.setPosition(x, y);
}

Item::~Item()
{

}

sf::FloatRect Item::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

void Item::update()
{

}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
