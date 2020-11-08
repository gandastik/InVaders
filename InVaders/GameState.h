#pragma once

#include "Player.h"
#include "GameState.h"
#include "Bullet.h"
#include "Platform.h"
#include "MainMenuState.h"
#include "Enemy.h"

class GameState :
	public State
{
private:
	sf::Event gameEvent;

	//Resources
	sf::Music bg_music;

	//GUI
	sf::RectangleShape hpBarOutline;
	sf::RectangleShape hpBar;

	//Background
	sf::Sprite background;
	sf::Texture backgroundTexture;

	//View
	sf::View view;
	sf::Vector2f viewPos;
	float currentCamera;
	bool moveCamera;
	float nextViewPos;

	//Player
	Player* player;

	//Enemy
	std::vector<Enemy*> enemies;

	//Bullets
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	sf::Clock shootTimer;

	//Platform
	std::vector<Platform*> platforms;
	sf::Vector2f direction;

	//Initialization
	void initPlatform();
	void initVariables();
	void initBackground();
	void initMusic();
	void initTexture();
	void initPlayer();
	void initEnemy();
	void initView();
	void initGUI();
	void initKeybinds();

public:
	//Constructure & Destructure
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void endState();
	
	//Update
	void updateInput(const float& dt);
	void updatePlayer(const float& dt);
	void updateEnemy(const float& dt);
	void updateCollision(const float& dt);
	void updateBullet();
	void updateGUI();
	void update(const float& dt);
	
	//Render
	void renderPlayer();
	void render(sf::RenderTarget* target = nullptr);
};

