#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationComponent.h"
#include "Hitbox.h"

class Item
{
private:
	sf::Texture texture;
	sf::RectangleShape shape;
	std::string type;
	sf::Sprite* sprite;

	AnimationComponent* animationComponent;

	//Hitbox
	Hitbox* hitbox;

	void initAnimationComponent();

public:
	Item(sf::Texture* texture, std::string type, float x, float y);
	~Item();

	//Accessors
	sf::FloatRect getGlobalBounds();
	const std::string& getType() const;

	//Components
	void createAnimationComponent();
	void createHitbox(float offset_x, float offset_y, float width, float height);

	//Functions
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget* target);
};

