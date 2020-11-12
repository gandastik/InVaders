#pragma once

#include <SFML/Graphics.hpp>

class Item
{
private:
	sf::Texture texture;
	sf::RectangleShape shape;


public:
	Item(sf::Texture* texture, float x, float y);
	~Item();

	//Accessors
	sf::FloatRect getGlobalBounds();

	//Functions
	void update();

	//Render
	void render(sf::RenderTarget* target);
};

