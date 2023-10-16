#include "../../include/systems/Systems.h"
#include"../../include/components/TTLComponent.h"
#include <iostream>

TTLSystem::TTLSystem()
{
	componentMask.turnOnBit(static_cast <int>(ComponentID::TTL));
	std::cout << "adasdas";
}

void TTLSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	if (entityRef->getTTLComponent() != nullptr)
	{
		entityRef->getTTLComponent()->decreaseTTL();
		if (entityRef->getTTLComponent()->getTtl() <= 0)
			entityRef->deleteEntity();
	}
	else
	{
		throw "No such Component Exists";
	}
}