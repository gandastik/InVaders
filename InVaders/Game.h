#pragma once
#include "Player.h"
#include "GameState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event ev;

	sf::Clock dtClock;
	float dt;
	
	std::stack<State*> states;

	Player* player;
	
	//Initialization
	void initWindow();
	void initStates();
	void initPlayer();

public:
	//Contructors / Destructors
	Game();
	~Game();

	//Functions
	void updateDt();
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	void run();
	const sf::RenderWindow& getWindow() const;
};

