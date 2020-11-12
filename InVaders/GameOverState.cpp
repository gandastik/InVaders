#include "stdafx.h"
#include "GameOverState.h"

//Initializer Functions
void GameOverState::initVariables()
{

}

void GameOverState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/game_over.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void GameOverState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/gameover.png"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE GAMEOVER" << std::endl;
	}
	this->background.setTexture(&this->backgroundTexture);
	this->background.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->view->getCenter().y - this->window->getSize().y / 2.f);
}

void GameOverState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/04font.ttf"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE 04FONT" << std::endl;
	}
}

void GameOverState::initKeybinds()
{
	std::ifstream ifs("config/gameoverstate_keybinds.ini");

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

void GameOverState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(this->view->getCenter().x - 125.f, this->view->getCenter().y + 140, 150, 50, &this->font, "NEW GAME",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

GameOverState::GameOverState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view)
	:State(window, supportedKeys, states, view)
{
	this->initVariables();
	this->initBackground();
	this->initButtons();
	this->initFonts();
	this->initKeybinds();
	this->initMusic();
}

GameOverState::~GameOverState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void GameOverState::endState()
{
	this->bg_music.stop();
	std::cout << "Ending Game Over State" << std::endl;
}

void GameOverState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}
	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->view));
		this->bg_music.stop();
	}
}

void GameOverState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void GameOverState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void GameOverState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}
