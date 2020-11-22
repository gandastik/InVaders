#include "stdafx.h"
#include "MainMenuState.h"



//Initializer Functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/intro.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x)
		, static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/wallpaper.jpg"))
	{
		std::cout << "ERROR::MAIN_MENU_STATE::FAILED TO LOAD BACKGROUND TO TEXTURE" << std::endl;
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/04font.ttf"))
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
	this->buttons["CREATE_NAME"] = new Button(this->window->getSize().x / 2.f - 75, 200, 150, 50, &this->font, "NEW GAME",
		sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(this->window->getSize().x / 2.f - 75, 400, 150, 50, &this->font, "QUIT",
		sf::Color(100, 100, 100, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
	this->buttons["SCORE_BOARD"] = new Button(this->window->getSize().x / 2.f - 75, 300, 150, 50, &this->font, "SCORE BOARD",
		sf::Color(100, 100, 100, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	:State(window, supportedKeys, states, view, player)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initMusic();
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
	if (this->buttons["CREATE_NAME"]->isPressed())
	{
		this->states->push(new CreateNameState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
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
	while (this->window->pollEvent(this->menuEvent))
	{
	
	}
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

	
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
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
