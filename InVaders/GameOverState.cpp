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

void GameOverState::initHighScore()
{
	this->fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(this->fp, "%s", &this->temp);
		this->name[i] = this->temp;
		fscanf(this->fp, "%d", &this->score[i]);
		this->userScore.push_back(std::make_pair(this->score[i], this->name[i]));
	}
	this->name[5] = this->player->getName();
	this->score[5] = this->player->getScore();
	this->userScore.push_back(std::make_pair(this->score[5], this->name[5]));
	std::sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fp);
	fopen("./score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(this->temp, this->userScore[i].second.c_str());
		fprintf(this->fp, "%s %d\n", this->temp, this->userScore[i].first);
	}
	fclose(this->fp);
	/*for (int i = 0; i < 5; i++)
	{
		std::cout << nameScore[i].second << " " << nameScore[i].first << std::endl;
	}*/
	
}

void GameOverState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(this->view->getCenter().x - 75.f, this->view->getCenter().y + this->window->getSize().y / 2.f - 160 , 150, 50, &this->font, "NEW GAME", 30,
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->buttons["MAIN_MENU"] = new Button(this->view->getCenter().x + this->window->getSize().x / 2.f - 170.f, this->view->getCenter().y + this->window->getSize().y / 2.f - 70, 150, 50, &this->font, "BACK TO MENU", 20,
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

GameOverState::GameOverState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	:State(window, supportedKeys, states, view, player)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initHighScore();
	this->initButtons();
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
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new CreateNameState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
	if (this->buttons["MAIN_MENU"]->isPressed())
	{
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states, this->view, this->player));
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
