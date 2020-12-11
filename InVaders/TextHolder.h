#pragma once
class TextHolder
{
private:
	sf::Font font;
	sf::Text text;
	sf::String string;
	sf::String Output;
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Clock textTimer;
	int iterator;

	//Sound Effects
	std::map<std::string, sf::SoundBuffer*> soundEffects;
	sf::Sound typingSound;

	//Initialization
	void initFont();
	void initSoundEffects();
	void initVariables();

public:
	TextHolder(float pos_x, float pos_y, float sizeX, float sizeY, sf::String text);
	~TextHolder();

	void setPosition(float x, float y);

	void update(const float& dt);

	void render(sf::RenderTarget* target);
};