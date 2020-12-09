#include "stdafx.h"
#include "CreateNameState.h"

//Initializer
void CreateNameState::initVariables()
{
	this->player = new Player();
	this->player->setPosition(0.f, 0.f);
	this->textHolder.setFillColor(sf::Color::Transparent);
	this->textHolder.setSize(sf::Vector2f(200.f, 50.f));
	this->textHolder.setOutlineThickness(2.f);
	this->textHolder.setOutlineColor(sf::Color::White);
	this->textHolder.setPosition(sf::Vector2f(this->view->getCenter().x - 110, 300.f));
}

void CreateNameState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/intro.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void CreateNameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/04font.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void CreateNameState::initText()
{
	this->input = "";
	this->text.setFont(this->font);
	this->text.setCharacterSize(25.f);
	this->text.setPosition(sf::Vector2f(this->view->getCenter().x - 100, 310.f));
}

void CreateNameState::initKeybinds()
{
	std::ifstream ifs("config/createnamestate_keybinds.ini");

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

void CreateNameState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(this->view->getCenter().x - 100, 400, 200, 50, &this->font, "START GAME", 30,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
}

CreateNameState::CreateNameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	this->initVariables();
	this->initMusic();
	this->initFont();
	this->initText();
	this->initKeybinds();
	this->initButtons();

}

CreateNameState::~CreateNameState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void CreateNameState::endState()
{
	std::cout << "Ending CreateNameState" << std::endl;
}

void CreateNameState::updateButtons()
{
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Start
	if (this->buttons["GAME_STATE"]->isPressed() && !this->nameString.empty())
	{
		this->player->setName(this->nameString);
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
}

void CreateNameState::updateInput(const float& dt)
{
	this->checkForQuit();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("NEW_GAME"))) && !this->nameString.empty())
	{
		this->player->setName(this->nameString);
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
}

void CreateNameState::update(const float& dt)
{
	while (this->window->pollEvent(this->nameEvent))
	{
		if (this->nameEvent.type == sf::Event::TextEntered)
		{
			if (this->nameEvent.text.unicode < 128)
			{
				std::cout << "Text entered: " << (this->nameEvent.text.unicode) << std::endl;
				if (this->nameEvent.text.unicode == static_cast<sf::Uint32>(8) && this->input.getSize() > 0)
				{
					this->input.erase(this->input.getSize() - 1);
					this->nameString.erase(this->nameString.size() - 1);
				}
				else
				{
					if (this->input.getSize() < 13 && this->nameEvent.text.unicode != 13)
					{
						if (this->nameEvent.text.unicode >= 97 && this->nameEvent.text.unicode <= 122)
						{
							this->nameEvent.text.unicode -= 32;
						}
						this->input += this->nameEvent.text.unicode;
						this->nameString += this->nameEvent.text.unicode;
					}
				}

			}
		}
	}
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

	
	this->text.setString(this->input);
}

void CreateNameState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void CreateNameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(target);

	target->draw(this->textHolder);
	target->draw(this->text);
}
