#include "stdafx.h"
#include "Game.h"

//Initializer function
void Game::initWindow()
{
	//create window using window config file
	 /*setting default values*/
	std::ifstream config("Config/window.ini");
	std::string title = "none";
	sf::VideoMode window_bounds(800, 600);
	unsigned framelate_limit = 60;
	bool vertical_sync_enabled = false;

	if (config.is_open())
	{
		std::getline(config, title);
		config >> window_bounds.width >> window_bounds.height;
		config >> framelate_limit;
		config >> vertical_sync_enabled;
	}

	config.close();

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(framelate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

void Game::initPlayer()
{
	this->player = new Player();
}

//Constructors / Destructors
Game::Game()
{
	this->initPlayer();
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->player;
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::updateDt()
{
	//update dt	valuable with the time it take to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
	//system("cls");
	std::cout << this->dt << "\n";
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, this->window->getSize().y - this->player->getGlobalBounds().height);
	}
}

void Game::update()
{
	//polling window events
	while (this->window->pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed)
			window->close();
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			window->close();
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::S ||
				this->ev.key.code == sf::Keyboard::D )
			)
		{
			this->player->restAnimationTimer();
		}

	}
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->updatePlayer();

	this->updateCollision();

}

void Game::renderPlayer()
{
	this->player->render(*this->window);
}

void Game::render()
{
	this->window->clear();

	//render item
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->renderPlayer();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		//this->updateDt();
		this->update();
		this->render();
	}
}

const sf::RenderWindow& Game::getWindow() const
{
	return *this->window;
}
