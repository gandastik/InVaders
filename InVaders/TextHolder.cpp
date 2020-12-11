#include "stdafx.h"
#include "TextHolder.h"

void TextHolder::initFont()
{
	if (!this->font.loadFromFile("Fonts/DTM-Mono.otf"))
	{
		std::cout << "ERROR::COULD NOT LOAD DTM-mono FONT" << std::endl;
	}
}

void TextHolder::initSoundEffects()
{
	this->soundEffects["Typing"] = new sf::SoundBuffer;
	this->soundEffects["Typing"]->loadFromFile("Resources/Sound Effects/typing.wav");

	this->typingSound.setBuffer(*this->soundEffects["Typing"]);
	this->typingSound.setVolume(10.f);
}

void TextHolder::initVariables()
{
	this->iterator = 0;
	this->Output = "";
}

TextHolder::TextHolder(float pos_x, float pos_y, float sizeX, float sizeY, sf::String text)
{
	this->initVariables();
	this->initFont();
	this->initSoundEffects();

	this->string = text;
	this->text.setFont(this->font);
	this->text.setCharacterSize(40.f);
	this->text.setFillColor(sf::Color::White);
	//this->text.setString(text);
	this->text.setPosition(pos_x + 20, pos_y + 20);

	this->position.x = pos_x;
	this->position.y = pos_y;
	this->shape.setPosition(this->position);
	this->shape.setFillColor(sf::Color::Black);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness(10.f);
	this->shape.setSize(sf::Vector2f(sizeX, sizeY));

	this->typingSound.play();
}

TextHolder::~TextHolder()
{
	//delete Sound Effects
	for (auto& i : this->soundEffects)
	{
		delete i.second;
	}
}

void TextHolder::setPosition(float x, float y)
{
	this->text.setPosition(x + 20, y + 20);
	this->shape.setPosition(x, y);
}

void TextHolder::update(const float& dt)
{
	if(iterator <= this->string.getSize()-1 && this->textTimer.getElapsedTime().asSeconds() >= 0.025f)
	{
		this->Output += this->string[this->iterator];
		this->iterator++;
		this->textTimer.restart();
	}
	this->text.setString(this->Output);
}

void TextHolder::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
