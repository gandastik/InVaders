#include "stdafx.h"
#include "Game.h"

//Initializer function

void Game::initWindow()
{
	//create window using window config file
	 /*setting default values*/
	std::ifstream config("Config/window.ini");
	std::string title = "none";
	this->windowBounds.width = 800;
	this->windowBounds.height = 600;
	unsigned framelate_limit = 60;
	bool vertical_sync_enabled = false;

	if (config.is_open())
	{
		std::getline(config, title);
		config >> this->windowBounds.width >> this->windowBounds.height;
		config >> framelate_limit;
		config >> vertical_sync_enabled;
	}

	config.close();

	this->window = new sf::RenderWindow(this->windowBounds, title, sf::Style::Default);
	this->window->setFramerateLimit(framelate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initVariables()
{
	this->shootCooldownMax = 15.f;
	this->shootCooldown = this->shootCooldownMax;
}


void Game::initBackground()
{
	if(!this->backgroundTexture.loadFromFile("Texture/bg.png"))
		std::cout << "ERROR::GAME::Could not load bg.png!" << "\n";
	this->background.setTexture(this->backgroundTexture);
	this->background.setTextureRect({ 0, 0, 2373, 208 });
	this->background.setScale(3.f, 3.f);

	if (!this->platformTexture.loadFromFile("Texture/platform.png"))
		std::cout << "ERROR::GAME::Could not load  platform.png!" << std::endl;
	this->platform.setTexture(this->platformTexture);
	this->platform.setTextureRect({ 0, 0, 1606, 208 });
	this->platform.setScale(3.f, 3.f);
}

void Game::initTexture()
{
	this->textures["BULLET"] = new sf::Texture;
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
	this->textures["FLIPPED_BULLET"] = new sf::Texture;
	this->textures["FLIPPED_BULLET"]->loadFromFile("Texture/flipped_bullet.png");
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initView()
{
	this->viewPos.x = this->window->getSize().x / 2;
	this->viewPos.y = this->window->getSize().y / 2;
	this->view.setSize(sf::Vector2f(this->windowBounds.width, this->windowBounds.height));
	this->currentCamera = this->window->getSize().x - 50.f;
	this->moveCamera = false;
	this->nextViewPos = viewPos.x;
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initPlayer();
	this->initWindow();
	this->initStates();
	this->initBackground();
	this->initView();
	this->initTexture();
}

Game::~Game()
{
	delete this->player;
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
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

}



//Functions
bool Game::canShoot()
{
	if (this->shootCooldown >= this->shootCooldownMax)
	{
		this->shootCooldown = 0.f;
		return true;
	}
	return false;
}

void Game::updateShootCooldown()
{
	if (this->shootCooldown < this->shootCooldownMax)
	{
		this->shootCooldown += 0.5f;
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::updateDt()
{
	//update dt	valuable with the time it take to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
	//system("cls");
	//std::cout << this->dt << "\n";
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->canShoot())
	{
		if(this->player->getIsFaceRight())
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x + this->player->getGlobalBounds().width, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, 1.f, 0.f, 10.f));
		else
			this->bullets.push_back(new Bullet(this->textures["FLIPPED_BULLET"], this->player->getPosition().x, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, -1.f, 0.f, 10.f));
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->canShoot() && this->player->getIsFaceRight() == false)
	{
		std::cout << "DONE" << std::endl;
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f, -1.f, 0.f, 5.f));
	}*/
}

void Game::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void Game::updateCollision(const float& dt)
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > 520.f)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 520.f - this->player->getGlobalBounds().height);
		this->player->setOnGround();
	}
	//Collision with the left side of screen
	if (this->player->getPosition().x < 0)
	{
		this->player->setPosition(0.f, this->player->getPosition().y);
	}
}

void Game::updateBullet()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (right screen)
		if (bullet->getBounds().left + bullet->getBounds().width > this->nextViewPos * 2.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		if (bullet->getBounds().left < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << std::endl;
		}
	}

	++counter;
}

void Game::update(const float& dt)
{
	//std::cout << this->currentCamera << " " << this->viewPos.x << std::endl;
	//polling window events
	while (this->window->pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed)
			window->close();
		/*if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			window->close();*/
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::Right ||
				this->ev.key.code == sf::Keyboard::S ||
				this->ev.key.code == sf::Keyboard::Left )
			)
		{
			this->player->restAnimationTimer();
			this->player->resetAnimationState();
		}
	}
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application End
	else
	{
		this->endApplication();
		this->window->close();
	}

	if (this->player->getPosition().x + 10.f > this->currentCamera)
	{
		this->currentCamera += this->window->getSize().x - 100;
		this->moveCamera = true;
		this->nextViewPos += this->window->getSize().x - 100;
	}
	/*else
	{
		this->viewpos.x = this->window->getsize().x / 2;
		this->movecamera = false;
	}*/

	if (this->viewPos.x < this->nextViewPos && this->moveCamera) this->viewPos.x += 2.f;
	else this->moveCamera = false;

	this->view.setCenter(this->viewPos);

	this->window->setView(this->view);

	this->updateInput();

	this->updatePlayer(dt);

	this->updateBullet();
	this->updateShootCooldown();
	
	this->updateCollision(dt);
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window->clear();

	//render item
	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	
	this->window->draw(this->background);
	this->window->draw(this->platform);
	
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->renderPlayer();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update(this->dt);
		this->render();
	}
}

const sf::RenderWindow& Game::getWindow() const
{
	return *this->window;
}
