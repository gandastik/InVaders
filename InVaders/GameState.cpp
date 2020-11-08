#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

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
void GameState::initPlatform()
{
	this->direction.x = 0.f;
	this->direction.y = 0.f;
	//Ground
	this->platforms.push_back(new Platform(this->textures["PLATFORM1"], sf::Vector2f(-5.f, 610.f)));
	//Stair
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3816.f, 567.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3858.f, 525.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3900.f, 483.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3921.f, 462.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(4005.f, 389.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM3"], sf::Vector2f(3972.f, 388.5f)));
}

void GameState::initVariables()
{
}

void GameState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Texture/bg.png"))
		std::cout << "ERROR::GAME::Could not load bg.png!" << "\n";
	this->background.setTexture(this->backgroundTexture);
	this->background.setTextureRect({ 0, 0, 4304, 223 });
	this->background.setScale(3.f, 3.5f);
}

void GameState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/bg_music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void GameState::initTexture()
{
	this->textures["BULLET"] = new sf::Texture;
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
	this->textures["FLIPPED_BULLET"] = new sf::Texture;
	this->textures["FLIPPED_BULLET"]->loadFromFile("Texture/flipped_bullet.png");
	this->textures["PLATFORM1"] = new sf::Texture;
	this->textures["PLATFORM1"]->loadFromFile("Texture/platform1.png");
	this->textures["PLATFORM2"] = new sf::Texture;
	this->textures["PLATFORM2"]->loadFromFile("Texture/platform2.png");
	this->textures["PLATFORM3"] = new sf::Texture;
	this->textures["PLATFORM3"]->loadFromFile("Texture/platform3.png");
	this->textures["ENEMY1"] = new sf::Texture;
	this->textures["ENEMY1"]->loadFromFile("Texture/Enemy/enemy.png");
}

void GameState::initPlayer()
{
	this->player = new Player();
}

void GameState::initEnemy()
{
	this->enemies.push_back(new Enemy(this->textures["ENEMY1"], 900.f, 520.f));
	this->enemies.push_back(new Enemy(this->textures["ENEMY1"], 1248.f, 535.f));
}

void GameState::initView()
{
	this->viewPos.x = this->window->getSize().x / 2;
	this->viewPos.y = this->window->getSize().y / 2;
	this->view.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->currentCamera = this->window->getSize().x - 50.f;
	this->moveCamera = false;
	this->nextViewPos = viewPos.x;
}

void GameState::initGUI()
{
	this->hpBar.setPosition(10.f, 10.f);
	this->hpBar.setSize(sf::Vector2f(20.f * this->player->getHp(), 20.f));
	this->hpBar.setFillColor(sf::Color::Red);

	this->hpBarOutline.setPosition(10.f, 10.f);
	this->hpBarOutline.setSize(sf::Vector2f(20.f * this->player->getHp(), 20.f));
	this->hpBarOutline.setOutlineThickness(2.f);
	this->hpBarOutline.setOutlineColor(sf::Color::Black);
	this->hpBarOutline.setFillColor(sf::Color::Transparent);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initTexture();
	this->initVariables();
	this->initPlayer();
	this->initEnemy();
	this->initMusic();
	this->initPlatform();
	this->initKeybinds();
	this->initBackground();
	this->initView();
	this->initGUI();
}

GameState::~GameState()
{
	delete this->player;
	//delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	//delete platforms
	for (auto* platform : this->platforms)
	{
		delete platform;
	}
	//delete Enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
}

void GameState::endState()
{
	std::cout << "Ending Game State!" << "\n";
	this->bg_music.stop();
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= 0.25f)
		{
			if (this->player->getIsFaceRight())
				this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x + this->player->getGlobalBounds().width, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, 1.f, 0.f, 10.f));
			else
				this->bullets.push_back(new Bullet(this->textures["FLIPPED_BULLET"], this->player->getPosition().x, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, -1.f, 0.f, 10.f));
			this->shootTimer.restart();
		}
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameState::updateEnemy(const float& dt)
{
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player);
	}
}

void GameState::updateCollision(const float& dt)
{
	if (this->player->getPosition().x < 0)
	{
		this->player->setPosition(0.f, this->player->getPosition().y);
	}
	unsigned counter = 0;
	for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		if (platform->getCollider().checkCollision(this->player->getCollider(), this->direction, 1.f))
		{
			this->player->onCollision(this->direction);
			this->player->resetVelocityY();
		}
		else if (!Collision::BoundingBoxTest(this->player->getSprite(), platform->getSprite()))
		{
			this->player->setOnGround(0);
		}
		for (auto* bullet : this->bullets)
		{
			//Bullet collide with platforms
			if (platform->getCollider().checkCollision(bullet->getCollider(), this->direction, 1.f))
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
		}
	}
	counter++;
}

void GameState::updateBullet()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (right screen)
		if (bullet->getBounds().left + bullet->getBounds().width > this->nextViewPos * 2.f - 100.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		if (bullet->getBounds().left < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		int temp = 0;
		//check if bullet hit the enemy(ies)
		for (auto* enemy : this->enemies)
		{
			if (bullet->getCollider().checkCollision(enemy->getCollider(), this->direction, 0.f))
			{
				std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				if (enemy->getHp() == 0)
				{
					delete this->enemies.at(temp);
					this->enemies.erase(this->enemies.begin() + temp);
				}
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
			temp++;
		}

	}
	++counter;
}

void GameState::updateGUI()
{
	this->hpBarOutline.setPosition(this->view.getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view.getCenter().y - this->window->getSize().y / 2.f + 10.f);
	this->hpBar.setPosition(this->view.getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view.getCenter().y - this->window->getSize().y / 2.f + 10.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 20.f, 20.f));
}

void GameState::update(const float& dt)
{
	while (this->window->pollEvent(this->gameEvent))
	{
		if (sf::Event::KeyReleased && (this->gameEvent.key.code == sf::Keyboard::A ||
			this->gameEvent.key.code == sf::Keyboard::D ||
			this->gameEvent.key.code == sf::Keyboard::Right ||
			this->gameEvent.key.code == sf::Keyboard::S ||
			this->gameEvent.key.code == sf::Keyboard::Left)
			)
		{
			this->player->restAnimationTimer();
			this->player->resetAnimationState();
		}
	}
	

	if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->currentCamera)
	{
		this->currentCamera += this->window->getSize().x - 100;
		this->moveCamera = true;
		this->nextViewPos += this->window->getSize().x - 100;
	}

	if (this->viewPos.x < this->nextViewPos && this->moveCamera) this->viewPos.x += 300.f * dt;
	else this->moveCamera = false;

	this->window->setView(this->view);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateBullet();
	this->updatePlayer(dt);
	this->updateEnemy(dt);

	if (this->player->getHp() <= 0)
	{
		this->quit = true;
	}

	this->updateGUI();

	this->view.setCenter(this->viewPos);

	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void GameState::renderPlayer()
{
	this->player->render(this->window);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//render item
	for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		platform->render(this->window);
	}

	this->window->draw(this->background);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->renderPlayer();

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->window->draw(this->hpBarOutline);
	this->window->draw(this->hpBar);
}