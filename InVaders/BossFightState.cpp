#include "stdafx.h"
#include "BossFightState.h"

void BossFightState::initPlatform()
{
	this->direction.x = 0.f;
	this->direction.y = 0.f;
	//Ground
	this->platforms.push_back(new Platform(this->textures["PLATFORM1"], sf::Vector2f(0.f, 615.f)));

	//Air platforms
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(175.f, 336.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(620.f, 258.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM3"], sf::Vector2f(1898.f, 318.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM4"], sf::Vector2f(1767.f, 220.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM2"], sf::Vector2f(2474.f, 317.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM5"], sf::Vector2f(2342.f, 219.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM3"], sf::Vector2f(2915.f, 236.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM3"], sf::Vector2f(3170.f, 316.f * 1.5f)));
	this->platforms.push_back(new Platform(this->textures["PLATFORM6"], sf::Vector2f(3499.f, 219.f * 1.5f)));
}

void BossFightState::initVariables()
{
	this->score = 0;
	this->changeColor = 255;
	this->endgame = false;
	this->isSpawn = false;
}

void BossFightState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Texture//boss_scene/boss_scene_bg.png"))
		std::cout << "ERROR::GAME::Could not load bg.png!" << "\n";
	this->background.setTexture(this->backgroundTexture);
	//this->background.setTextureRect({ 0, 0, 4304, 223 });
	this->background.setScale(1.f, 1.5f);
}

void BossFightState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/boss_scene_music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void BossFightState::initSoundEffects()
{
	this->soundEffects["PICKUP_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_SOUND"]->loadFromFile("Resources/Sound Effects/pick_up_item.wav");
	this->soundEffects["PICKUP_BONUS_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_BONUS_SOUND"]->loadFromFile("Resources/Sound Effects/power_up.wav");

	this->pickUpItemSound.setBuffer(*this->soundEffects["PICKUP_SOUND"]);
	this->pickUpItemSound.setVolume(10.f);
	this->pickUpBonusItemSound.setBuffer(*this->soundEffects["PICKUP_BONUS_SOUND"]);
	this->pickUpBonusItemSound.setVolume(10.f);
}

void BossFightState::initTexture()
{
	this->textures["BULLET"] = new sf::Texture;
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
	this->textures["FLIPPED_BULLET"] = new sf::Texture;
	this->textures["FLIPPED_BULLET"]->loadFromFile("Texture/flipped_bullet.png");
	this->textures["PLATFORM1"] = new sf::Texture;
	this->textures["PLATFORM1"]->loadFromFile("Texture/boss_scene/platform1.png");
	this->textures["PLATFORM2"] = new sf::Texture;
	this->textures["PLATFORM2"]->loadFromFile("Texture/boss_scene/platform2.png");
	this->textures["PLATFORM3"] = new sf::Texture;
	this->textures["PLATFORM3"]->loadFromFile("Texture/boss_scene/platform3.png");
	this->textures["PLATFORM4"] = new sf::Texture;
	this->textures["PLATFORM4"]->loadFromFile("Texture/boss_scene/platform4.png");
	this->textures["PLATFORM5"] = new sf::Texture;
	this->textures["PLATFORM5"]->loadFromFile("Texture/boss_scene/platform5.png");	
	this->textures["PLATFORM6"] = new sf::Texture;
	this->textures["PLATFORM6"]->loadFromFile("Texture/boss_scene/platform6.png");
	this->textures["HEALTH"] = new sf::Texture;
	this->textures["HEALTH"]->loadFromFile("Texture/Item/healthPack.png");
	this->textures["BONUS"] = new sf::Texture;
	this->textures["BONUS"]->loadFromFile("Texture/Item/bonus.png");
	this->textures["ENEMY"] = new sf::Texture;
	this->textures["ENEMY"]->loadFromFile("Texture/Enemy/enemy.png");
	this->textures["BOSS"] = new sf::Texture;
	this->textures["BOSS"]->loadFromFile("Texture/boss_scene/boss.png");
}

void BossFightState::initPlayer()
{
	this->player->setPosition(0, 300);
}

void BossFightState::initEnemy()
{
	this->enemies.push_back(new Enemy(this->textures["BOSS"], "BOSS", 2000, 520));
}

void BossFightState::initItem()
{
	this->items.push_back(new Item(this->textures["HEALTH"], "HEAL", 669.f, 234.f * 1.5f));
	this->items.push_back(new Item(this->textures["BONUS"], "BONUS", 749.f, 230.f * 1.5f));
}

void BossFightState::initView()
{
	this->view = new sf::View;
	this->viewPos.x = this->window->getSize().x / 2;
	this->viewPos.y = this->window->getSize().y / 2;
	this->view->setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->currentCamera = this->window->getSize().x - 50.f;
	this->moveCamera = false;
	this->nextViewPos = viewPos.x;
}

void BossFightState::initGUI()
{
	this->hpBar.setPosition(10.f, 35.f);
	this->hpBar.setSize(sf::Vector2f(10.f * this->player->getHp(), 20.f));
	this->hpBar.setFillColor(sf::Color::Red);

	this->hpBarOutline.setPosition(10.f, 35.f);
	this->hpBarOutline.setSize(sf::Vector2f(10.f * this->player->getMaxHp(), 20.f));
	this->hpBarOutline.setOutlineThickness(2.f);
	this->hpBarOutline.setOutlineColor(sf::Color::Black);
	this->hpBarOutline.setFillColor(sf::Color::Transparent);

	this->BonusItemIcon.setTexture(this->textures["BONUS"]);
	this->BonusItemIcon.setSize(sf::Vector2f(30.f, 30.f));
	this->BonusItemIcon.setPosition(20.f, 60.f);

	this->bossHpBar.setPosition(40.f, this->window->getSize().y - 30.f);
	this->bossHpBar.setSize(sf::Vector2f(30.f * this->enemies.at(0)->getHp(), 20.f));
	this->bossHpBar.setFillColor(sf::Color::Red);

	this->bossHpBarOutline.setPosition(40.f, this->window->getSize().y - 30.f);
	this->bossHpBarOutline.setSize(sf::Vector2f(30.f * this->enemies.at(0)->getHp(), 20.f));
	this->bossHpBarOutline.setOutlineThickness(2.f);
	this->bossHpBarOutline.setOutlineColor(sf::Color::Black);
	this->bossHpBarOutline.setFillColor(sf::Color::Transparent);

	if (!this->scoreFont.loadFromFile("Fonts/04font.ttf"))
		std::cout << "ERROR::GAME_STATE::COULD NOT LOAD SCOREFONT FROM FILE" << std::endl;
	this->scoreText.setFont(this->scoreFont);
	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setCharacterSize(30.f);
	this->scoreText.setFillColor(sf::Color(250, 220, 0, 250));
	this->scoreText.setOutlineThickness(2.f);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);

	this->playerName.setFont(this->scoreFont);
	this->playerName.setString(this->player->getName());
	this->playerName.setCharacterSize(20.f);
	this->playerName.setFillColor(sf::Color(255, 255, 255, 255));
	this->playerName.setOutlineThickness(2.f);
	this->playerName.setOutlineColor(sf::Color::Black);
	this->playerName.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + this->playerName.getGlobalBounds().width + 10.f, 5.f);
}

void BossFightState::initKeybinds()
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

BossFightState::BossFightState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	this->initTexture();
	this->initVariables();
	this->initPlayer();
	this->initEnemy();
	this->initMusic();
	this->initSoundEffects();
	this->initPlatform();
	this->initKeybinds();
	this->initBackground();
	this->initItem();
	this->initView();
	this->initGUI();
}

BossFightState::~BossFightState()
{
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

void BossFightState::endState()
{
	std::cout << "Ending Boss Fight State!" << std::endl;
	this->bg_music.stop();
}

void BossFightState::spawnEnemy()
{

}

void BossFightState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			if (this->player->getIsFaceRight())
				this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x + this->player->getGlobalBounds().width, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, 1.f, 0.f, 10.f));
			else
				this->bullets.push_back(new Bullet(this->textures["FLIPPED_BULLET"], this->player->getPosition().x, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, -1.f, 0.f, 10.f));
			this->shootTimer.restart();
		}
	}
}

void BossFightState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void BossFightState::updateEnemy(const float& dt)
{
	int temp = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player, dt);
		if (enemy->getType() == "BOSS" && enemy->getHp() <= enemy->getMaxHp() / 2 && !this->isSpawn)
		{
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % 600 + int(this->window->getSize().x / 2.f + static_cast<int>(this->view->getCenter().x)), rand() % 41 + 500));
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % 600 + int(this->window->getSize().x / 2.f + static_cast<int>(this->view->getCenter().x)), rand() % 41 + 500));
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % 600 + int(this->window->getSize().x / 2.f + static_cast<int>(this->view->getCenter().x)), rand() % 41 + 500));
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % int(static_cast<int>(this->view->getCenter().x) - this->window->getSize().x / 2.f), rand() % 41 + 500));
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % int(static_cast<int>(this->view->getCenter().x) - this->window->getSize().x / 2.f), rand() % 41 + 500));
			this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % int(static_cast<int>(this->view->getCenter().x) - this->window->getSize().x / 2.f), rand() % 41 + 500));
			this->isSpawn = true;
		}
		if (enemy->getHp() <= 0)
		{
			if (enemy->getIsDeath() && enemy->getType() == "SOLDIER")
			{
				this->endgame = true;
				delete this->enemies.at(temp);
				this->enemies.erase(this->enemies.begin() + temp);
				temp--;
			}
		}
		temp++;
	}
}

void BossFightState::updateCollision(const float& dt)
{
	//Check collision between the left side of the WINDOW
	if (this->player->getPosition().x < this->view->getCenter().x - this->window->getSize().x / 2.f)
	{
		this->player->setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->player->getPosition().y);
	}
	//Check collision between player and the end of the map
	if (this->player->getPosition().x + this->player->getGlobalBounds().width >= this->backgroundTexture.getSize().x)
	{
		this->player->setPosition(this->backgroundTexture.getSize().x - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}
	//Check collision between the PLAYER and PLATFORMS
	unsigned counter = 0;
	for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		if (platform->getCollider().checkCollision(this->player->getCollider(),this->player->getSprite(), this->direction, 1.f))
		{
			this->player->onCollision(this->direction, dt);
			this->player->resetVelocityY();
		}
		else if (!Collision::BoundingBoxTest(this->player->getSprite(), platform->getSprite()))
		{
			this->player->setOnGround(0);
		}
		for (auto* bullet : this->bullets)
		{
			//PLAYER'S BULLETS collide with PLATFORMS
			if (platform->getCollider().checkCollision(bullet->getCollider(), bullet->getSprite(), this->direction, 1.f))
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
		}
	}
	counter++;
}

void BossFightState::updateItemsCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : this->items)
	{
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getHp() < this->player->getMaxHp() && item->getType() == "HEAL")
		{
			delete this->items.at(itemCounter);
			this->player->heal(1);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "BONUS")
		{
			delete this->items.at(itemCounter);
			this->player->reduceShootCD();
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpBonusItemSound.play();
			--itemCounter;
		}
		++itemCounter;
	}
}

void BossFightState::updateBullet(const float& dt)
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
		if (bullet->getBounds().left < this->view->getCenter().x - this->window->getSize().x / 2.f - 50)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//bullet collision with the enemy
		for (auto* enemy : this->enemies)
		{
			if (bullet->getBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
			{
				//std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				////if enemy's hp is 0
				if (enemy->getHp() == 0)
				{
					this->player->addScore(enemy->getPoint());
					if (enemy->getIsDrop())
						this->items.push_back(new Item(this->textures["HEALTH"], "HEAL", enemy->getPosition().x, enemy->getPosition().y + enemy->getGlobalBounds().height - 40.f));
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

void BossFightState::updateGUI(const float& dt)
{

	this->hpBarOutline.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 10.f, 20.f));

	this->BonusItemIcon.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 20.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 60.f);
	this->BonusItemIcon.setFillColor(sf::Color(255, 255, 255, this->changeColor -= 500 * dt));

	this->bossHpBarOutline.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 40.f, this->view->getCenter().y + this->window->getSize().y / 2.f - 30.f);
	this->bossHpBar.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 40.f, this->view->getCenter().y + this->window->getSize().y / 2.f - 30.f);
	this->bossHpBar.setSize(sf::Vector2f(this->enemies.at(0)->getHp() * 30.f, 20.f));

	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);

	this->playerName.setString(this->player->getName());
	this->playerName.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, 5.f);
}

void BossFightState::update(const float& dt)
{
	while (this->window->pollEvent(this->ev))
	{

	}
	//Move screen when all the enemies in the screen is dead
	if (this->player->getPosition().x > this->window->getSize().x / 2.f && this->player->getPosition().x <= this->backgroundTexture.getSize().x - this->window->getSize().x / 2.f)
	{
		this->view->setCenter(this->player->getPosition().x, this->window->getSize().y / 2.f);
	}
	else if (this->player->getPosition().x > this->backgroundTexture.getSize().x - this->window->getSize().x / 2.f)
	{
		this->view->setCenter(this->backgroundTexture.getSize().x - this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	}
	else
	{
		this->view->setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	}
	this->spawnEnemy();

	this->window->setView(*this->view);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateItemsCollision(dt);
	this->updateBullet(dt);
	this->updatePlayer(dt);
	this->updateEnemy(dt);


	this->updateGUI(dt);

	//this->view->setCenter(this->viewPos);

	if (this->player->getHp() <= 0)
	{
		this->states->pop();
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
	
}

void BossFightState::renderPlayer()
{
	this->player->render(this->window);
}

void BossFightState::renderGUI()
{
	this->window->draw(this->hpBar);
	this->window->draw(this->hpBarOutline);
	
	this->window->draw(this->bossHpBar);
	this->window->draw(this->bossHpBarOutline);

	if (this->player->getBonusState())
		this->window->draw(this->BonusItemIcon);
	else this->changeColor = 255;

	this->window->draw(this->scoreText);
	this->window->draw(this->playerName);
}

void BossFightState::render(sf::RenderTarget* target)
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

	for (auto* item : this->items)
	{
		item->render(this->window);
	}

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderPlayer();

	this->renderGUI();
}
