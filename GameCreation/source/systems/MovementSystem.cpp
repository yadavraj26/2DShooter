#include "../../include/systems/Systems.h"
#include"../../include/components/VelocityComponent.h"
#include"../../include/components/PositionComponent.h"

MovementSystem::MovementSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::Position));
	componentMask.turnOnBit(static_cast<int>(ComponentID::Velocity));
}

void MovementSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	if (entityRef->getPositionComponent() != nullptr && entityRef->getVelocityComponent() != nullptr)
	{
		Vector2f pos = entityRef->getPosition() + (entityRef->getVelocityComponent()->getVelocity() * entityRef->getVelocityComponent()->getSpeed() * elapsed);
		entityRef->getPositionComponent()->setPosition(pos.x, pos.y);
	}
}