#pragma once

#include "stdafx.h"

class Hitbox
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~Hitbox();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getSprite() const;

	//Modifiers
	void setPosition(sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	bool Intersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

