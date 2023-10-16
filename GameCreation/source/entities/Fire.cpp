#include "../../include/entities/Fire.h"
#include"../../include/components/GraphicsComponent.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
	ttl = std::make_shared<TTLComponent>(startTimeToLive);
	addComponent(ttl);
	velocity = std::make_shared<VelocityComponent>();
	addComponent(velocity);
	//next = nullptr;
}

Fire::~Fire()
{}


/*void Fire::update(Game* game, float elapsed)
{
	// XI.C First, update the position of the Fire object by calling the parent Entity::update() function.
	Entity::update(game, elapsed);
	velocity->update(*this, elapsed);
	// XI.D Time to live (Fire::ttl member variable) needs to be reduced by 1 at every frame. If this gets
	//		to 0, the entity must be deleted (here, just setting the deleted flat to ture).
	

}*/
