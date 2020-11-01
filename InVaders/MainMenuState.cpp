#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Montserrat-Black.otf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, "NEW GAME",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50, &this->font, "QUIT",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
} 

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end();++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	std::cout << "Ending Main Menu State" << std::endl;
}

void MainMenuState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Start
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Quit
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

	
	
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}
