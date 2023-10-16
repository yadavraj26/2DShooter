#include "../../include/systems/Systems.h"
#include "../../include/components/ColliderComponet.h"
#include"../../include/core/Game.h"



PrintDebugSystem::PrintDebugSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::Collider));
}

void PrintDebugSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	draw(gameRef, entityRef, gameRef->getWindow());
}

void PrintDebugSystem::draw(Game* gameRef, Entity* entityRef, Window* windowRef)
{
	windowRef->draw(entityRef->getColliderComponent()->getBoundingBox().getDrawableRect());
}