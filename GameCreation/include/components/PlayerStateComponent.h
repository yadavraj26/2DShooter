#pragma once
#include"LogicComponent.h"
#include"../../include/Service/Subject.h"
#include"../../include/entities/Entity.h"
#include"../../include/entities/Fire.h"
#include"../../include/core/Game.h"

class Audio;

class PlayerStateComponent:public LogicComponent, public Subject
{
public:
	const int shootingCost = 5;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = .1f;
	const int maxWood = 100;


	PlayerStateComponent();
	void update(Game* gameRef, Entity* entityRef, float elapsed) override;
	bool isAttacking()const { return attacking;}
	bool isShouting()const { return shouting; }
	const int getWood()const { return wood; }

	void addWood(int wood);
	void setAttacking(bool attack) { attacking = attack; }
	void setWood(bool woodAmount) { wood = woodAmount; }
	void setShouting(bool shout) { shouting = shout; }
	ComponentID getID() { return ComponentID::Logic; }



private:
	

	bool attacking;
	bool shouting;
	float shootCooldown;
	int wood = 60;

	//Acheivements
	int noOfShouts;

	//Audio Service
	std::shared_ptr<Audio> plActionAudioService;

};