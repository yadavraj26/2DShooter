#include"../../include/systems/Systems.h"
#include"../../include/components/ColliderComponet.h"
#include"../../include/components/PositionComponent.h"
#include "../../include/core/Game.h"

ColliderSystem::ColliderSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::Collider));
	componentMask.turnOnBit(static_cast<int>(ComponentID::Position));
}

void ColliderSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	
	
	if (entityRef->getEntityType() != EntityType::POTION && entityRef->getEntityType() != EntityType::LOG)
		entityRef->getColliderComponent()->setBoundingBox(entityRef->getPosition(),
			Vector2f(entityRef->getPosition().x + entityRef->getColliderComponent()->getBoxSize().x,
					entityRef->getPosition().y + entityRef->getColliderComponent()->getBoxSize().y));
	

	//gameRef->getWindow()->draw(entityRef->getColliderComponent()->getBoundingBox().getDrawableRect());
}

