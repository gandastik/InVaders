#pragma once

#include "Player.h"
#include "GameState.h"
#include "Bullet.h"
#include "Platform.h"
#include "MainMenuState.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "Item.h"
#include "BossFightState.h"
#include "TextHolder.h"

class GameState2 :
	public State
{
private:
	sf::Event ev;

	//Resources
	sf::Music bg_music;

	//GUI
	sf::RectangleShape hpBarOutline;
	sf::RectangleShape hpBar;
	sf::RectangleShape BonusItemIcon;
	sf::Text playerName;
	int changeColor;
	sf::Font scoreFont;
	sf::Text scoreText;
	int score;
	sf::Sprite KeySprite;

	//Background
	sf::Sprite background;
	sf::Texture backgroundTexture;

	//Enemy
	std::vector<Enemy*> enemies;
	sf::Vector2f enemyDirection;

	//Items
	std::vector<Item*> items;
	
	//Sound Effects
	std::map<std::string, sf::SoundBuffer*> soundEffects;
	sf::Sound pickUpHealthSound;
	sf::Sound pickUpCoinSound;
	sf::Sound pickUpPooSound;
	sf::Sound pickUpChickenSound;
	sf::Sound openDoorSound;

	//View
	sf::Vector2f viewPos;
	float currentCamera;
	bool moveCamera;
	float nextViewPos;

	//Bullets
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	sf::Clock shootTimer;

	//Platform
	std::vector<Platform*> platforms;
	sf::Vector2f direction;

	//Door
	bool haveKey;
	bool isPressed;

	//Components
	std::vector<TextHolder*> textHolder;
	sf::Clock textTimer;

	//Initialization
	void initPlatform();
	void initVariables();
	void initBackground();
	void initMusic();
	void initSoundEffects();
	void initTexture();
	void initPlayer();
	void initEnemy();
	void initItem();
	void initView();
	void initGUI();
	void initKeybinds();

public:
	//Constructure & Destructure
	GameState2(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~GameState2();

	//Functions
	void endState();
	void spawnEnemies();
	void createTextHolder(float pos_x, float pos_y, float sizeX, float sizeY, sf::String text);

	//Update
	void updateViewPosition();
	void updateInput(const float& dt);
	void updatePlayer(const float& dt);
	void updateEnemy(const float& dt);
	void updateCollision(const float& dt);
	void updateItemsCollision(const float& dt);
	void updateBullet(const float& dt);
	void updateGUI(const float& dt);
	void update(const float& dt);

	//Render
	void renderPlayer();

	void renderGUI();
	void render(sf::RenderTarget* target = nullptr);
};


