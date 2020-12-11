#pragma once

#include "Player.h"
#include "GameState.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "Item.h"
#include "EndGameState.h"

class BossFightState:
	public State
{
private:
	sf::Event ev;
	bool endgame;
	bool isIgnore;
	sf::Clock collisionTimer;

	//Resources
	sf::Music bg_music;

	//GUI
	sf::RectangleShape hpBarOutline;
	sf::RectangleShape hpBar;
	sf::RectangleShape BonusItemIcon;
	sf::RectangleShape bossHpBarOutline;
	sf::RectangleShape bossHpBar;
	sf::Text playerName;
	int changeColor;
	sf::Font scoreFont;
	sf::Text scoreText;
	int score;

	//Background
	sf::Sprite background;
	sf::Texture backgroundTexture;

	//View
	sf::Vector2f viewPos;
	float currentCamera;
	bool moveCamera;
	float nextViewPos;

	//Player
	sf::Clock meleeCooldown;

	//Enemy
	std::vector<Enemy*> enemies;
	sf::Clock spawnClock;
	bool isSpawn;

	//Bullets
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	sf::Clock shootTimer;

	//Items
	std::vector<Item*> items;
	std::map<std::string, sf::SoundBuffer*> soundEffects;

	//Sound Effects
	sf::Sound pickUpItemSound;
	sf::Sound pickUpBonusItemSound;
	sf::Sound meleeSound;

	//Platform
	std::vector<Platform*> platforms;
	sf::Vector2f direction;

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
	BossFightState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~BossFightState();

	//Functions
	void endState();

	//Update
	void spawnEnemy();
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

