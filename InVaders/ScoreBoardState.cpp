#include "stdafx.h"
#include "ScoreBoardState.h"

void ScoreBoardState::initVariables()
{
}

void ScoreBoardState::initMusic()
{
}

void ScoreBoardState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/gameover.png"))
	{
		std::cout << "ERROR::SCOREBOARDSTATE::COULD NOT LOAD FROM FILE GAMEOVER" << std::endl;
	}
	this->background.setTexture(&this->backgroundTexture);
	this->background.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->view->getCenter().y - this->window->getSize().y / 2.f);
}

void ScoreBoardState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/04font.ttf"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE 04FONT" << std::endl;
	}
}

void ScoreBoardState::initText()
{
	this->scoreBoardText.setFont(this->font);
	this->scoreBoardText.setCharacterSize(40.f);
	this->scoreBoardText.setFillColor(sf::Color::White);
	this->scoreBoardText.setString("..SCOREBOARD..");
	this->scoreBoardText.setPosition(this->view->getCenter().x - 140.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 40.f);

	for (int i = 0; i < 5; i++)
	{
		this->playerName[i].setFont(this->font);
		this->playerName[i].setCharacterSize(22.f);
		this->playerName[i].setFillColor(sf::Color::White);
		this->playerName[i].setPosition(this->view->getCenter().x - 140, this->view->getCenter().y - this->window->getSize().y / 2.f + 100.f + (100 * i));
		this->playerScore[i].setFont(this->font);
		this->playerScore[i].setCharacterSize(22.f);
		this->playerScore[i].setFillColor(sf::Color::White);
		this->playerScore[i].setPosition(this->view->getCenter().x + 100, this->view->getCenter().y - this->window->getSize().y / 2.f +  100.f + (100 * i));
	}
}

void ScoreBoardState::initKeybinds()
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

void ScoreBoardState::initHighScore()
{
	this->fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(this->fp, "%s", &this->temp);
		this->name[i] = this->temp;
		this->playerName[i].setString(this->name[i]);
		fscanf(this->fp, "%d", &this->score[i]);
		this->playerScore[i].setString(std::to_string(this->score[i]));
		this->userScore.push_back(std::make_pair(this->score[i], this->name[i]));
	}

}

void ScoreBoardState::initButtons()
{
	this->buttons["MAIN_MENU"] = new Button(this->view->getCenter().x - 100.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 560, 220, 50, &this->font, "BACK TO MENU", 30,
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

ScoreBoardState::ScoreBoardState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	:State(window, supportedKeys, states, view, player)
{
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initHighScore();
	this->initText();
	this->initButtons();
}

ScoreBoardState::~ScoreBoardState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void ScoreBoardState::endState()
{
	std::cout << "Ending Score Board State" << std::endl;
}

void ScoreBoardState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//BACK TO MAIN MENU
	if (this->buttons["MAIN_MENU"]->isPressed())
	{
		this->states->pop();
	}
}

void ScoreBoardState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void ScoreBoardState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void ScoreBoardState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void ScoreBoardState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//target->draw(this->background);

	this->renderButtons(target);

	target->draw(this->scoreBoardText);

	for (int i = 0; i < 5; i++)
	{
		target->draw(this->playerName[i]);
		target->draw(this->playerScore[i]);
	}
}
