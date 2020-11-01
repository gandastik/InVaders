#pragma once
class Collider
{
private:

	sf::Sprite &body;

public:
	Collider(sf::Sprite& body);
	~Collider();

	//Accessor
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
	sf::FloatRect getGlobalBounds();

	void move(float dx, float dy);
	bool checkCollision(Collider other, sf::Vector2f& direction, float push);

};

