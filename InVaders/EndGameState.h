#pragma once

#include "State.h"
#include "Button.h"
#include "MainMenuState.h"

class EndGameState :
	public State
{
private:
	//Resources
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text text;
	//Highscore
	FILE* fp;
	char temp[255];
	int score[6];
	std::string name[6];
	std::vector <std::pair<int, std::string>> userScore;

	std::map<std::string, Button*>buttons;
	sf::Music bg_music;

	//Initialization
	void initVariables();
	void initMusic();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initHighScore();
	void initButtons();

public:
	EndGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~EndGameState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	//Render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

