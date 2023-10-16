#pragma once
#include "Entity.h"
#include"../../include/Service/Subject.h"
#include <memory.h>

class Fire;
class HealthComponent;
class ColliderComponent;
class InputComponent;
class VelocityComponent;
class PlayerStateComponent;
class Observer;

class Player :  public Entity, public Subject
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	

	Player();
	~Player();





	std::shared_ptr<HealthComponent> getHealthComp() { return health; }



	bool hasSpriteSheet() const { return isSpriteSheet; }
	

	void positionSprite(int row, int col, int spriteWH, float tileScale);
	

	std::shared_ptr<ColliderComponent> getColliderComponent()override { return collider; }

	std::shared_ptr<PlayerStateComponent> getPlayerStateComp() { return playerState; }
	std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }

	//systems
	std::shared_ptr<InputComponent> getInputComponent() override{ return playerInputHandler; }
	std::shared_ptr<VelocityComponent> getVelocityComponent() override  { return velocity; }
	std::shared_ptr<LogicComponent> getLogicComponent() override { return logicComp; }
	
	//Observer
	void setObserver(std::shared_ptr<Observer> observerRef) { assignObserver(observerRef); }

	//Acheivements
	void addPotion(int totalNoPotions);
	int getPotionCount() { return potionsCount; }

	//virtual void setNext(std::shared_ptr<Entity> nextItem)override{}

	//virtual std::shared_ptr<Entity> getNext()override { return nullptr; } 


private:



	std::shared_ptr<InputComponent> playerInputHandler;

	std::shared_ptr <HealthComponent> health;

	std::shared_ptr<VelocityComponent> velocity;

	std::shared_ptr<ColliderComponent> collider;

	std::shared_ptr<LogicComponent> logicComp;

	std::shared_ptr<PlayerStateComponent> playerState;

	//Acheivements
	int potionsCount=0;


};

