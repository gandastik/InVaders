#include "stdafx.h"
#include "Game.h"

//Initializer function

void Game::initWindow()
{
	//create window using window config file
	 /*setting default values*/
	std::ifstream config("Config/window.ini");
	this->VideoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "none";
	this->windowBounds.width = 800;
	this->windowBounds.height = 600;
	unsigned framelate_limit = 60;
	bool vertical_sync_enabled = false;

	if (config.is_open())
	{
		std::getline(config, title);
		config >> this->windowBounds.width >> this->windowBounds.height;
		config >> framelate_limit;
		config >> vertical_sync_enabled;
	}

	config.close();

	this->window = new sf::RenderWindow(this->windowBounds, title, sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(framelate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initVariables()
{
}

void Game::initKeys()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

}

void Game::initStates()
{
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states, &this->view, this->player));
}

//Constructors / Destructors
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}



//Functions
void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::updateDt()
{
	//update dt	valuable with the time it take to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
	if (this->dt > 1.0f / 60)
		this->dt = 1.f / 60.f;
	//system("cls");
	//std::cout << this->dt << "\n";
}

void Game::update(const float& dt)
{
	//std::cout << this->currentCamera << " " << this->viewPos.x << std::endl;
	//polling window events
	//while (this->window->pollEvent(this->ev)) 
	//{
	//	if (this->ev.type == sf::Event::Closed)
	//		window->close();
	//	/*if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
	//		window->close();*/
	//}
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application End
	else
	{
		this->endApplication();
		this->window->close();
	}

}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update(this->dt);
		this->render();
	}
}

const sf::RenderWindow& Game::getWindow() const
{
	return *this->window;
}
