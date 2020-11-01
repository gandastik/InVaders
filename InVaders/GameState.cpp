#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
}

GameState::~GameState()
{
	
}

void GameState::endState()
{
	std::cout << "Ending Game State!" << "\n";
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
}
