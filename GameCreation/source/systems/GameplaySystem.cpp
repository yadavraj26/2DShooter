#include "../../include/systems/Systems.h"
#include "../../include/components/LogicComponent.h"

GameplaySystem::GameplaySystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::Logic));
}

void GameplaySystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	entityRef->getLogicComponent()->update(gameRef, entityRef, elapsed);
}