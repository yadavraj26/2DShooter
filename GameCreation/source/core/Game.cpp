#pragma once
#include "../../include/core/Game.h"
#include"../../include/core/Command.h"
#include"../../include/entities/Entity.h"
//#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/components/GraphicsComponent.h"
#include"../../include/components/HealthComponent.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include"../../include/components/PlayerStateComponent.h"
#include"../../include/systems/Systems.h"
#include"../../include/components/InputComponent.h"
#include"../../include/core/InputHandler.h"
#include "../../include/Service/Locator.h"
#include"../../include/Service/AudioManager.h"
//#include"../../include/entities/EntityPool.h"
#include <iostream>
#include<memory>

// Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false), counter(0), totalPotions(0), potionsCount(0)
{
	// Create the unique pointer to the Input Handler object.
	input = std::make_unique<InputHandler>();
	std::shared_ptr<InputSystem> inputSystem = std::make_shared<InputSystem>();
	logicSystems.push_back(inputSystem);
	std::shared_ptr<MovementSystem> movementSystem = std::make_shared<MovementSystem>();
	logicSystems.push_back(movementSystem);
	std::shared_ptr<GameplaySystem> entityLogic = std::make_shared<GameplaySystem>();
	logicSystems.push_back(entityLogic);
	std::shared_ptr<ColliderSystem> colliderSystem = std::make_shared<ColliderSystem>();
	logicSystems.push_back(colliderSystem);
	std::shared_ptr<TTLSystem> ttlSystem = std::make_shared<TTLSystem>();
	logicSystems.push_back(ttlSystem);

	std::shared_ptr<GraphicsSystem> graphicsSystem = std::make_shared<GraphicsSystem>();
	graphicsSystems.push_back(graphicsSystem);
	std::shared_ptr<PrintDebugSystem> printDebugSystem = std::make_shared<PrintDebugSystem>();
	graphicsSystems.push_back(printDebugSystem);

	acheivementObserver = std::make_shared<Acheivements>();


	//Audio Manager
	audioM = std::make_shared<AudioManager>();

	potionPool = std::make_unique<EntityPool<Potion>>();
	logPool = std::make_unique<EntityPool<Log>>();
	firePool = std::make_shared<EntityPool<Fire>>();

	//pPool = new EntityPool<Potion>();

}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(std::shared_ptr<T> entity, const std::string& filename, int col, int row)
{

	//auto ent = std::make_shared<T>();
	//auto ent = pPool->instantiate(filename, itemScale);
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;
	//ent->setPosition(x + cntrFactor, y + cntrFactor);
	entity->setPosition(x + cntrFactor, y + cntrFactor);
	
	entity->init(filename, itemScale);
	return std::shared_ptr<T>(entity);
}

void Game::buildBoard(size_t width, size_t height)
{
	// Instantiate the unique pointer of type "Board". 
	// Use the constructor of Board that receives the width and the height for the game grid.
	board = std::make_unique<Board>(width, height);

	//std::make_unique<Board> board(width, height);

}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	//firePool->getEntity();
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");

	auto it = lines.cbegin();
	int row = 0;

	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if (w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);
		}

		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				//Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);

				break;
			}
			case 'x':
			{
				auto ent = logPool->getEntity();

				if (ent != nullptr)
				{
					addEntity(buildEntityAt<Log>(ent, "img/log.png", col, row));
				}
				else
				{
					std::cerr<<"\nNo more Log objects in Pool\n";
				}

				//By default, entities stand on corridors
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'p':
			{
				auto ent = potionPool->getEntity();
				if (ent != nullptr)
				{
					addEntity(buildEntityAt<Potion>(ent, "img/potion.png", col, row));
					totalPotions++;
				}
				else
				{
					std::cerr << "\nNo more Potion objects in Pool\n";
				}

				//By default, entities stand on corridors
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case '*':
			{

				// Create the player shared pointer.
				player = std::make_shared<Player>();

				// Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				// This string should be "img/DwarfSpriteSheet_data.txt"
				player->initSpriteSheet("img/DwarfSpriteSheet_data.txt", "Idle", true, true);

				// Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				// Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				// and the scale for the tiles (const float Game::tileScale)
				player->positionSprite(row, col, spriteWH, tileScale);

				// Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);
				player->setObserver(acheivementObserver);
				player->getPlayerStateComp()->assignObserver(acheivementObserver);

				//By default, entities stand on corridors:
				//Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			}

			col++; is++;
		}
		row++; it++;
	}
	assignAcheivementOb();


}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	// This function adds an entity, received by parameter, to the collection of entities.
	// This must: Increase the entity counter (note: the very first entity should have a ID = 1).
	// Assign the ID to the entity received by parameter. iii) Add the entity to the vector of entities of this class.
	counter++;
	newEntity->setID(counter);
	entities.push_back(newEntity);
}

void Game::handleInput()
{
	// Call the fucntion that handles the input for the game and retrieve the command returned in a variable.
	// Then, call the "execute" method of the returned object to run this command.
	auto command = input->handleInput();
	if (command != nullptr) command->execute(*this);
	// Call the function handleInput on the player's object.

}


void Game::update(float elapsed)
{
	
	bigArray(logicSystems, elapsed);
	std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin();
	while (it < entities.end())
	{
		if ((*it)->getID() == player->getID()|| (*it)->getColliderComponent()==nullptr || (*it)->isDeleted())
		{
			it++;
			continue;
		}
		if (player->getColliderComponent()->intersects(((*it)->getColliderComponent())))
		{
			switch ((*it)->getEntityType())
			{
			case EntityType::POTION:
				player->getHealthComp()->changeHealth(dynamic_cast<Potion*>(it->get())->getHealth());
				(*it)->deleteEntity();
				getPlayer()->addPotion(totalPotions);
				Locator::getAudioService(AudioObjectID::PlayerPickup)->playSound(AudioID::PotionPickup);
				std::cout << dynamic_cast<Potion*>(it->get())->getHealth() << "\t" << player->getHealthComp()->getHealth() << std::endl;
				break;
			case EntityType::LOG:
				if (player->getGraphicsComponent()->getCurrentAnim().getName() == "Attack" && player->getGraphicsComponent()->getCurrentAnimFrame() == 4)
				{
					player->getPlayerStateComp()->addWood(dynamic_cast<Log*>(it->get())->getWood());
					std::cout << dynamic_cast<Log*>(it->get())->getWood() << "\t" << player->getPlayerStateComp()->getWood() << std::endl;
					(*it)->deleteEntity();

				}
				break;
			default:
				std::cout << (int)(*it)->getEntityType() << std::endl;
				break;
			}
		}
		it++;
	}


	it = entities.begin();
	while (it < entities.end())
	{
		if ((*it)->isDeleted())
		{
			switch (it->get()->getEntityType())
			{
			case EntityType::POTION:
				potionPool->hibernate(*it);
				break;
			case EntityType::LOG:
				logPool->hibernate(*it);
				break;
			case EntityType::FIRE:
				firePool->hibernate(*it);
				break;
			default:
				break;
			}
			it = entities.erase(it);
			//deleteEntity(*it);
			continue;
		}
		it++;
	}

	


//Update the window for refreshing the graphics (leave this OUTSIDE the !paused block)
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	//draw board bg
	board->draw(&window);

	//call graphic systems
	bigArray(graphicsSystems, elapsed);


	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

//Return the current ID counter.
EntityID Game::getIDCounter()
{
	return counter;  
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	// Return the pointer to the entity which is in position "idx" of the vector.
	// must verify that the index is within the bounds of the vector.
	if (idx < entities.size())
	{
		return entities.at(idx);
	}

	return nullptr;
}

void Game::changeInput()
{
	auto playerInputComp = dynamic_cast<PlayerInputComponent&> (*getPlayer()->getInputComponent());
	//playerInputComp.getPlayerInputHandler()->changeKeyBinding(playerInputComp.getPlayerInputHandler()->getCommand(CommandID::MoveUp), sf::Keyboard::Up);
	playerInputComp.getPlayerInputHandler()->changeMovementKeys();
}

void Game::bigArray(std::vector<std::shared_ptr<System>> system, float elapsed)
{
	std::vector<std::shared_ptr<System>>::iterator it = system.begin();
	while (it < system.end())
	{
		std::vector<std::shared_ptr<Entity>>::iterator etIt = entities.begin();
		while (etIt < entities.end())
		{
			if ((!(*etIt)->isDeleted()) && (*it)->validate(etIt->get()))
			{
				(*it)->update(this, etIt->get(), elapsed);
			}
			etIt++;
		}

		it++;
	}
}

void Game::assignAcheivementOb()
{
	player->assignObserver(acheivementObserver);
	player->getPlayerStateComp()->assignObserver(acheivementObserver);
}





template<class T>
EntityPool<T> Game::getEntityPool(EntityType eType)
{
	switch (eType)
	{
	case EntityType::POTION:
		return potionPool;
	case EntityType::LOG:
		return logPool;
	case EntityType::FIRE:
		return firePool;
	default:
		return nullptr;
	}
}

template <class T>
std::shared_ptr<T> Game::getEntity(EntityType eType)
{
	switch (eType)
	{
	case EntityType::POTION:
		return potionPool->getEntity();
	case EntityType::LOG:
		return logPool->getEntity();
	case EntityType::FIRE:
		return firePool->getEntity();
	default:
		return nullptr;
	}
}