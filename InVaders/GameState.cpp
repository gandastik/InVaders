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
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3837.f, 546.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3858.f, 525.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3879.f, 504.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3900.f, 483.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3921.f, 462.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3942.f, 453.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3963.f, 431.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(3984.f, 410.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(4005.f, 389.f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM3"], sf::Vector2f(3972.f, 388.5f)));
}

void GameState::initVariables()
{
	this->score = 0;
	this->checkPoint = 1;
	this->done = false;
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
	this->bg_music.setVolume(5.f);
	this->bg_music.play();
}

void GameState::initSoundEffects()
{
	if (!this->pickUpItemsfx.loadFromFile("Resources/Sound Effects/pick_up_item.wav"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD FROM FILE SOUNDEFFECTS" << std::endl;
	}
	this->pickUpItemSound.setBuffer(this->pickUpItemsfx);
	this->pickUpItemSound.setVolume(10.f);
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
	this->textures["ENEMY"] = new sf::Texture;
	this->textures["ENEMY"]->loadFromFile("Texture/Enemy/enemy.png");
	this->textures["HEALTH"] = new sf::Texture;
	this->textures["HEALTH"]->loadFromFile("Texture/healthPack.png");
}

void GameState::initPlayer()
{
	this->player = new Player();
}

//void GameState::initEnemy()
//{
//	this->enemies.push_back(new Enemy(this->textures["ENEMY"], 1150.f, 100.f));
//	this->enemies.push_back(new Enemy(this->textures["ENEMY"], 1250.f, 100.f));
//}

void GameState::initView()
{
	this->view = new sf::View;
	this->viewPos.x = this->window->getSize().x / 2;
	this->viewPos.y = this->window->getSize().y / 2;
	this->view->setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
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

	if (!this->scoreFont.loadFromFile("Fonts/04font.ttf"))
		std::cout << "ERROR::GAME_STATE::COULD NOT LOAD SCOREFONT FROM FILE" << std::endl;
	this->scoreText.setFont(this->scoreFont);
	this->scoreText.setString(std::to_string(this->score));
	this->scoreText.setCharacterSize(30.f);
	this->scoreText.setFillColor(sf::Color(250, 220, 0, 250));
	this->scoreText.setOutlineThickness(1.f);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view)
	: State(window, supportedKeys, states, view)
{
	this->initTexture();
	this->initVariables();
	this->initPlayer();
	//this->initEnemy();
	this->initMusic();
	this->initSoundEffects();
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
	//delete Items
	for (auto* item : this->items)
	{
		delete item;
	}
}

void GameState::endState()
{
	std::cout << "Ending Game State!" << "\n";
	this->bg_music.stop();
}

void GameState::spawnEnemies()
{
	/*
		note : enemies can only spawn between 500-540 in Y-axis
		condition : random spawn enemy in X-axis between the center of the screen 
		and the end of the screen every views move
	*/
	//std::cout << this->checkPoint << std::endl;
	if (this->checkPoint == 1 && !this->done)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x), rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 2 && !this->done /*&& !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 3 && !this->done /*&& !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 4 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", 4180.f, 300.f));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", 4290.f, 300.f));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 5 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= 0.4f)
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
	int temp = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player, dt);
		if (enemy->getHp() <= 0)
		{
			if (enemy->getIsDeath())
			{
				delete this->enemies.at(temp);
				this->enemies.erase(this->enemies.begin() + temp);
				temp--;
			}
		}
		temp++;
	}
	
}

void GameState::updateCollision(const float& dt)
{
	//Check collision between the left side of the window
	if (this->player->getPosition().x < this->view->getCenter().x - this->window->getSize().x / 2.f)
	{
		this->player->setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->player->getPosition().y);
	}
	//Check collision between the player and platforms
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
	//Check the collision between enemies and platforms
	/*for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		for (auto* enemy : this->enemies)
		{
			if (platform->getCollider().checkCollision(enemy->getCollider(), this->direction, 1.f))
			{
				enemy->resetVelocityY();
				enemy->setOnGround();
			}
		}
	}*/
}

void GameState::updateItemsCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : this->items)
	{
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getHp() < 10)
		{
			delete this->items.at(itemCounter);
			this->player->heal(1);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		++itemCounter;
	}
}

void GameState::updateBullet(const float& dt)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (right screen)
		if (bullet->getBounds().left + bullet->getBounds().width > this->view->getCenter().x + this->window->getSize().x / 2.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//bullet culling (left screen)
		if (bullet->getBounds().left < this->view->getCenter().x - this->window->getSize().x / 2.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//int temp = 0;
		//check if bullet hit the enemy(ies)
		for (auto* enemy : this->enemies)
		{
			if (bullet->getCollider().checkCollision(enemy->getCollider(), this->direction, 0.f))
			{
				//std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				////if enemy's hp is 0
				if (enemy->getHp() == 0)
				{
					this->score += enemy->getPoint();
					if(enemy->getIsDrop())
						this->items.push_back(new Item(this->textures["HEALTH"], enemy->getPosition().x, enemy->getPosition().y + enemy->getGlobalBounds().height - 40.f));
				//	if (enemy->getIsDeath())
				//	{
				//		delete this->enemies.at(temp);
				//		this->enemies.erase(this->enemies.begin() + temp);
				//		temp--;
				//	}
				}
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
			//temp++;
		}

	}
	++counter;
}

void GameState::updateGUI()
{
	this->hpBarOutline.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 10.f);
	this->hpBar.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 10.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 20.f, 20.f));

	this->scoreText.setString(std::to_string(this->score));
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);
}

void GameState::update(const float& dt)
{
	while (this->window->pollEvent(this->gameEvent))
	{
		/*if (sf::Event::KeyReleased && (this->gameEvent.key.code == sf::Keyboard::A ||
			this->gameEvent.key.code == sf::Keyboard::D ||
			this->gameEvent.key.code == sf::Keyboard::Right ||
			this->gameEvent.key.code == sf::Keyboard::S ||
			this->gameEvent.key.code == sf::Keyboard::Left)
			)
		{
			this->player->restAnimationTimer();
			this->player->resetAnimationState();
		}*/
		/*if (this->gameEvent.type == sf::Event::TextEntered)
		{
			if (this->gameEvent.text.unicode < 128)
				std::cout << "Text entered: " << static_cast<char>(this->gameEvent.text.unicode) << std::endl;

		}*/
	}
	//Move screen when all the enemies in the screen is dead
	if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->currentCamera && this->enemies.size() == 0)
	{
		this->currentCamera += this->window->getSize().x - 100;
		this->moveCamera = true;
		this->nextViewPos += this->window->getSize().x - 100;
		this->done = false;
	}

	if (this->viewPos.x < this->nextViewPos && this->moveCamera) this->viewPos.x += 300.f * dt;
	else this->moveCamera = false;
	

	this->spawnEnemies();

	this->window->setView(*this->view);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateItemsCollision(dt);
	this->updateBullet(dt);
	this->updatePlayer(dt);
	
	this->updateEnemy(dt);

	this->updateGUI();

	this->view->setCenter(this->viewPos);

	if (this->player->getHp() <= 0)
	{
		this->states->pop();
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->view));
		this->bg_music.stop();
	}
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void GameState::renderPlayer()
{
	this->player->render(this->window);
}

void GameState::renderGUI()
{
	this->window->draw(this->hpBarOutline);
	this->window->draw(this->hpBar);
	this->window->draw(this->scoreText);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//render
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

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* item : this->items)
	{
		item->render(this->window);
	}

	this->renderPlayer();

	this->renderGUI();
}