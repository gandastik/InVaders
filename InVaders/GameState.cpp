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
}

void GameState::update(const float& dt)
{
	std::cout << "Hello From GameState" << "\n";
}

void GameState::render(sf::RenderTarget* target)
{
}
