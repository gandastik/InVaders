#pragma once
#include "Player.h"
#include "GameState.h"
#include "Bullet.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event ev;
	sf::VideoMode windowBounds;

	//Background
	sf::Sprite background;
	sf::Texture backgroundTexture;


	sf::Sprite platform;
	sf::Texture platformTexture;

	//View
	sf::View view;
	sf::Vector2f viewPos;
	float currentCamera;
	bool moveCamera;
	float nextViewPos;


	sf::Clock dtClock;
	float dt;
	
	std::stack<State*> states;

	//Player
	Player* player;

	//Bullets
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	float shootCooldown;
	float shootCooldownMax;
	bool canShoot();
	void updateShootCooldown();

	//Initialization
	void initVariables();
	void initWindow();
	void initBackground();
	void initTexture();
	void initStates();
	void initPlayer();
	void initView();

public:
	//Contructors / Destructors
	Game();
	~Game();

	//Functions
	void endApplication();

	//Update
	void updateDt();
	void updateInput();
	void updatePlayer(const float& dt );
	void updateCollision(const float& dt);
	void updateBullet();
	void update(const float& dt);
	//Render
	void renderPlayer();
	void render();
	//Core
	void run();
	const sf::RenderWindow& getWindow() const;
};

