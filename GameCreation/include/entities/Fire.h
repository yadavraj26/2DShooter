#pragma once
#include"../../include/components/VelocityComponent.h"
#include "../../include/components/TTLComponent.h"
#include "Entity.h"
//#include<memory>

class VelocityComponent;
class TTLComponent;
class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	int getTTL() const { return ttl->getTtl(); }

	//std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }

	std::shared_ptr<TTLComponent> getTTLComponent() { return ttl; }

	std::shared_ptr<VelocityComponent> getVelocityComponent() { return velocity; }


	void init(const std::string& textureFile, float scale) override
	{
		Entity::init(textureFile, scale);
		state.data.type = EntityType::FIRE;
		ttl->resetTTL(startTimeToLive);
	}

private:

	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;

	//Fire* next;
};

