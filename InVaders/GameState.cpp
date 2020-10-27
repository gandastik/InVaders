#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	: State(window)
{

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
	this->updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
}
