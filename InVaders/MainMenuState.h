#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);

};

