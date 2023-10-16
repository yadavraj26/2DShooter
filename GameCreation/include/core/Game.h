#pragma once
#include "../graphics/Window.h"
#include "../core/Board.h"
//#include"../../include/entities/Entity.h"
#include "../../include/Service/Subject.h"
#include"../../include/sound/Audio.h"
#include"../../include/entities/EntityPool.h"
//#include "../../include/entities/StaticEntities.h"
//#include"../../include/entities/Fire.h"

//#include "../entities/Player.h"
//#include<memory>
//#include<vector>

class Player;
class InputHandler;
class GraphicsComponent;
class System;
class Log;
class Potion;
class Fire;
class AudioManager;
//class Entity;
//class Board;
//class Player;
//class Window;
class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	void changeInput();
	bool isPaused() const { return paused; }
	
	template<class T>
	EntityPool<T> getEntityPool(EntityType eType);

	template <class T>
	std::shared_ptr<T> getEntity(EntityType eType);
	
	std::string fileName = "img/log.png";

	std::shared_ptr<Player> getPlayer() { return player; }

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(std::shared_ptr<T> entity, const std::string& textureFile, int col, int row);

	void bigArray(std::vector<std::shared_ptr<System>> system, float elapsed);

	/*void deleteEntity(std::shared_ptr<Potion>);
	void deleteEntity(std::shared_ptr<Log>);
	void deleteEntity(std::shared_ptr<Fire>);*/


	std::unique_ptr<EntityPool<Potion>> potionPool;
	std::unique_ptr<EntityPool<Log>> logPool;
	std::shared_ptr<EntityPool<Fire>> firePool;

private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;


	//Board
	std::unique_ptr<Board> board;
	Board board1;

	//Entities
	std::vector<std::shared_ptr<Entity>> entities;
	EntityID counter;

	// Declare a pointer to a player object.
	std::shared_ptr<Player> player;

	//Declare a unique pointer to an Input Handler object for this class.
	std::unique_ptr<InputHandler> input;


	std::shared_ptr<Observer> acheivementObserver;

	//Systems
	std::vector<std::shared_ptr<System>> logicSystems;
	std::vector<std::shared_ptr<System>> graphicsSystems;

	//Acheivements
	int potionsCount=0;
	int totalPotions=0;
	void assignAcheivementOb();

	//Audio Service
	std::shared_ptr<AudioManager> audioM;
};

