#pragma once
#include "State.h"
#include "GameState.h"

class CreateNameState :
	public State
{
private:
	sf::Event nameEvent;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;
	sf::String input;
	sf::Text text;

	std::map<std::string, Button*> buttons;

	sf::Music bg_music;

	//Initializer
	void initVariables();
	void initMusic();
	void initFont();
	void initText();
	void initKeybinds();
	void initButtons();

public:
	CreateNameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~CreateNameState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target);
};

