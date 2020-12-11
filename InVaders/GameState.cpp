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
	this->platforms.push_back(new Platform(sf::Vector2f(3816.f, 567.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3837.f, 546.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3858.f, 525.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3879.f, 504.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3900.f, 483.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3921.f, 462.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3942.f, 453.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3963.f, 431.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3984.f, 410.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4005.f, 389.f), sf::Vector2f(225.f, 79.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(3972.f, 388.5f), sf::Vector2f(465.f, 251.f), "stairL"));
}

void GameState::initVariables()
{
	this->score = 0;
	this->checkPoint = 1;
	this->done = false;
	this->isStart = false;
	this->changeColor = 255;
	this->door.setSize(sf::Vector2f(75.f, 182.f));
	this->door.setPosition(12645.f, 413.f);
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
	this->soundEffects["PICKUP_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_SOUND"]->loadFromFile("Resources/Sound Effects/pick_up_item.wav");
	this->soundEffects["PICKUP_BONUS_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_BONUS_SOUND"]->loadFromFile("Resources/Sound Effects/power_up.wav");
	this->soundEffects["MELEE_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["MELEE_SOUND"]->loadFromFile("Resources/Sound Effects/melee.wav");


	this->pickUpItemSound.setBuffer(*this->soundEffects["PICKUP_SOUND"]);
	this->pickUpItemSound.setVolume(10.f);
	this->pickUpBonusItemSound.setBuffer(*this->soundEffects["PICKUP_BONUS_SOUND"]);
	this->pickUpBonusItemSound.setVolume(10.f);
	this->meleeSound.setBuffer(*this->soundEffects["MELEE_SOUND"]);
	this->meleeSound.setVolume(10.f);
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
	this->textures["HEALTH"]->loadFromFile("Texture/Item/healthPack.png");
	this->textures["BONUS"] = new sf::Texture;
	this->textures["BONUS"]->loadFromFile("Texture/Item/bonus.png");
}

void GameState::initPlayer()
{

}

void GameState::initItem()
{
	this->items.push_back(new Item(this->textures["BONUS"], "BONUS", 1146, 553));
	this->items.push_back(new Item(this->textures["BONUS"], "BONUS", 4554, 553));
}

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

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
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
	this->initItem();
	this->initView();
	this->initGUI();

	this->createTextHolder(this->view->getCenter().x - this->window->getSize().x / 2.f + 500, this->view->getCenter().y - this->window->getSize().y / 2.f + 100,
		1000, 190.f, "YOUR MISSION IS TO FIND ALLEN O'NEIL \nAND PUT AN END TO HIS LIFE!");
}

GameState::~GameState()
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
	//delete Sound Effects
	for (auto& i : this->soundEffects)
	{
		delete i.second;
	}
	//delete Text
	for (auto* i : this->textHolder)
	{
		delete i;
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
		and the end of the screen in every checkpoint
	*/
	//std::cout << this->checkPoint << std::endl;
	if (this->checkPoint == 1 && !this->done)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x) + 200, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x) + 300, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->viewPos.x) + 400, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 2 && !this->done /*&& !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 300, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 3 && !this->done /*&& !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
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
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 300, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 300, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 6 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 7 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));		
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 8 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 200, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 9 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 10 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
	if (this->checkPoint == 11 && !this->done /* && !this->moveCamera*/)
	{
		std::cout << "DONE" << std::endl;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos), rand() % 41 + 500));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], "SOLDIER", rand() % this->window->getSize().x / 2.f + static_cast<int>(this->nextViewPos) + 100, rand() % 41 + 500));
		this->done = true;
		this->checkPoint++;
	}
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->player->getIsJump() == false)
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
	//Check collision between the left side of the WINDOW
	if (this->player->getPosition().x < this->view->getCenter().x - this->window->getSize().x / 2.f)
	{
		this->player->setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->player->getPosition().y);
	}
	/*if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->view->getCenter().x + this->window->getSize().x / 2.f)
	{
		this->player->setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}*/
	//Check collision between player and the end of the map
	if (this->player->getPosition().x + this->player->getGlobalBounds().width >= 12909)
	{
		this->player->setPosition(12909 - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}
	//Check collision between PLAYER and PORTAL DOOR and pressed UP arrow key to go to the next stage!
	if (this->door.getGlobalBounds().intersects(this->player->getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->states->pop();
		this->states->push(new GameState2(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
	//Check collision between the PLAYER and PLATFORMS
	unsigned counter = 0;
	for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		if (platform->getType() == "stairL" || platform->getType() == "stairR")
		{
			if (platform->getCollider().checkCollision(this->player->getCollider(), this->player->getSprite(), this->direction, 1.f, platform->getType()))
			{
				this->player->onCollision(this->direction, dt);
				//this->player->resetVelocityY();
			}
		}
		else if (platform->getCollider().checkCollision(this->player->getCollider(), this->player->getSprite(), this->direction, 1.f))
		{
			this->player->onCollision(this->direction, dt);
			//this->player->resetVelocityY();
		}
		else if (!Collision::BoundingBoxTest(this->player->getSprite(), platform->getSprite()))
		{
			this->player->setOnGround(0);
		}
		for (auto* bullet : this->bullets)
		{
			//PLAYER'S BULLETS collide with PLATFORMS
			if (platform->getBody().getGlobalBounds().intersects(bullet->getBounds()))
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
		}
	}
	counter++;
	//Check the collision between PLAYER and ENEMIES
	for (auto* enemy : this->enemies)
	{
		if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
		{
			if(this->meleeCooldown.getElapsedTime().asSeconds() >= 3.f)
			{
				this->player->Melee();
				this->meleeSound.play();
				this->meleeCooldown.restart();
				enemy->takeDmg(3);
				if (enemy->getHp() <= 0)
				{
					this->player->addScore(enemy->getPoint());
				}
			}
		}
	}
}

void GameState::createTextHolder(float pos_x, float pos_y, float sizeX, float sizeY, sf::String text)
{
	this->textHolder.push_back(new TextHolder(pos_x, pos_y, sizeX, sizeY, text));
}

void GameState::updateItemsCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : this->items)
	{
		item->update(dt);
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getHp() < this->player->getMaxHp() && item->getType() == "HEAL")
		{
			delete this->items.at(itemCounter);
			this->player->heal(1);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "BONUS" && !this->player->getIsShooting())
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

void GameState::updateBullet(const float& dt)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (right screen)
		if (bullet->getBounds().left + bullet->getBounds().width > this->view->getCenter().x + this->window->getSize().x / 2.f + 100.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//bullet culling (left screen)
		if (bullet->getBounds().left < this->view->getCenter().x - this->window->getSize().x / 2.f - 100.f)
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
			if (bullet->getBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
			{
				//std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				////if enemy's hp is 0
				if (enemy->getHp() == 0)
				{
					this->player->addScore(enemy->getPoint());
					if(enemy->getIsDrop())
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
		++counter;
	}
	
}

void GameState::updateGUI(const float& dt)
{
	if (this->player->getHp() > 20)
		this->player->setHP(this->player->getMaxHp());
	this->hpBarOutline.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 10.f, 20.f));

	this->BonusItemIcon.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 20.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 60.f);
	this->BonusItemIcon.setFillColor(sf::Color(255, 255, 255, this->changeColor-=500*dt));

	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);

	this->playerName.setString(this->player->getName());
	this->playerName.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, 5.f);

	for (auto* text : this->textHolder)
	{
		text->update(dt);
		text->setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 160, this->view->getCenter().y - this->window->getSize().y / 2.f + 80);
	}
	if (this->textTimer.getElapsedTime().asSeconds() >= 4.f)
	{
		this->isStart = true;
		this->textHolder.clear();
	}
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

	if (this->viewPos.x < this->nextViewPos && this->moveCamera && this->viewPos.x < 12270) this->viewPos.x += 300.f * dt;
	else this->moveCamera = false;
	
	if (this->isStart)
		this->spawnEnemies();

	this->window->setView(*this->view);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateItemsCollision(dt);
	this->updateBullet(dt);
	this->updatePlayer(dt);
	
	this->updateEnemy(dt);

	this->updateGUI(dt);

	this->view->setCenter(this->viewPos);

	if (this->player->getHp() <= 0)
	{
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->view, this->player));
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
	this->window->draw(this->hpBar);
	this->window->draw(this->hpBarOutline);

	if (this->player->getBonusState())
		this->window->draw(this->BonusItemIcon);
	else this->changeColor = 255;

	this->window->draw(this->scoreText);
	this->window->draw(this->playerName);

	for (auto* text : this->textHolder)
	{
		if (this->textTimer.getElapsedTime().asSeconds() <= 4.f)
		{
			text->render(this->window);
		}
	}
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

	//this->window->draw(this->door);

	this->renderPlayer();

	this->renderGUI();
}