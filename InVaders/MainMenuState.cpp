#include "stdafx.h"
#include "MainMenuState.h"



//Initializer Functions
void MainMenuState::initVariables()
{
	//this->view->setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
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
	this->background.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->view->getCenter().y - this->window->getSize().y / 2.f);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/04font.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
	if (!this->gameTitleFont.loadFromFile("Fonts/04font.ttf"))
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	if (!this->nameFont.loadFromFile("Fonts/DTM-mono.otf"))
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
}

void MainMenuState::initText()
{
	this->gameTitle.setFont(this->gameTitleFont);
	this->gameTitle.setCharacterSize(60.f);
	this->gameTitle.setLetterSpacing(1.6f);
	this->gameTitle.setOutlineThickness(5.f);
	this->gameTitle.setOutlineColor(sf::Color::Black);
	this->gameTitle.setPosition( this->view->getCenter().x - this->window->getSize().x / 2.f + 50.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 50.f);
	this->gameTitle.setString("METAL\nSLAUGTHER");

	this->name.setFont(this->nameFont);
	this->name.setStyle(sf::Text::Bold);
	this->name.setCharacterSize(20.f);
	this->name.setOutlineThickness(1.f);
	this->name.setOutlineColor(sf::Color::Black);
	this->name.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - 420.f, this->view->getCenter().y + this->window->getSize().y / 2.f - 30.f);
	this->name.setString("63010035 KITSADANG SAWANGSIRIPOL");
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
	this->buttons["CREATE_NAME"] = new Button(this->view->getCenter().x + this->window->getSize().x / 2.f - 400, this->view->getCenter().y - this->window->getSize().y / 2.f + 200, 250, 50, &this->font, "NEW GAME", 40,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
	this->buttons["EXIT_STATE"] = new Button(this->view->getCenter().x + this->window->getSize().x / 2.f - 400, this->view->getCenter().y - this->window->getSize().y / 2.f + 400, 250, 50, &this->font, "QUIT", 40,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
	this->buttons["SCORE_BOARD"] = new Button(this->view->getCenter().x + this->window->getSize().x / 2.f - 400, this->view->getCenter().y - this->window->getSize().y / 2.f + 300, 250, 50, &this->font, "SCORE BOARD", 40,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	:State(window, supportedKeys, states, view, player)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
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
		this->states->pop();
		this->states->push(new CreateNameState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}

	//SCOREBOARD
	if (this->buttons["SCORE_BOARD"]->isPressed())
	{
		this->states->push(new ScoreBoardState(this->window, this->supportedKeys, this->states, this->view, this->player));
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

	target->draw(this->gameTitle);
	
	target->draw(this->name);
}
