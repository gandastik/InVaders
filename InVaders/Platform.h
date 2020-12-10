#pragma once

#include "Collider.h"

class Platform
{
private:
	sf::Sprite sprite;
	sf::RectangleShape body;
	std::string type;
public:
	Platform(sf::Texture* texture, sf::Vector2f position);
	Platform(sf::Vector2f position, sf::Vector2f size, std::string type);
	~Platform();

	Collider getCollider();
	std::string getType();
	sf::RectangleShape getBody();
	sf::Sprite getSprite();


	void render(sf::RenderTarget* target);
};

