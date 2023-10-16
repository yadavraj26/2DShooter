#include "../../include/components/GraphicsComponent.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include<memory.h>

GraphicsSystem::GraphicsSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::Graphics));
	componentMask.turnOnBit(static_cast<int>(ComponentID::Position));
}

void GraphicsSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	
	entityRef->getGraphicsComponent()->setSpritePosition(entityRef->getPosition().x, entityRef->getPosition().y);
	//Switch statement can be used when the number of types increases
	if(entityRef->getGraphicsComponent()->graphicsType==GraphicsType::SpriteSheet)
	{
		entityRef->getGraphicsComponent()->getSpriteSheet()->update(elapsed);
	}
	//entityRef->getGraphicsComponent()->getSprite().setScale(2.f,2.f);
	draw(gameRef, entityRef, gameRef->getWindow());
	//gameRef->getWindow()->draw(entityRef->getGraphicsComponent()->getSprite());
}

void GraphicsSystem::draw(Game* gameRef, Entity* entityRef, Window* windowRef)
{
	windowRef->draw(entityRef->getGraphicsComponent()->getSprite());
}