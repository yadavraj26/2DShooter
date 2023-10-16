#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
//#include "../graphics/SpriteSheet.h"
//#include "../utils/Rectangle.h"
#include"../../include/components/PositionComponent.h"
#include"../../include/components/GraphicsComponent.h"
#include"../../include/components/ColliderComponet.h"
#include"../../include/components/TTLComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/utils/Bitmask.h"
#include<SFML/System/Vector2.hpp>
#include <iostream>
#include<memory>


Entity::Entity() :
	isSpriteSheet(false),
	deleted(false)
	// X.B (1/2) Add the initialization the deleted flag to false
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
	state.next = nullptr;
	//std::cout << sizeof(entityid);

}

Entity::Entity(EntityType et) :
	isSpriteSheet(false),
	deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
	std::cout << sizeof(double);
}

Entity::~Entity()
{
}




/*void Entity::draw(Window* window)
{
	
	//graphics->draw(window);
	
}*/

void Entity::init(const std::string& textureFile, float scale)
{
	if (graphics == nullptr)
	{
		graphics = std::make_shared<SimpleSpriteComponent>(textureFile, scale);
		addComponent(graphics);
	}
	//set boxsize of the collider 
	if(getColliderComponent()!=nullptr)
		getColliderComponent()->setBoxSize(graphics->getTextureSize().x * graphics->getSpriteScale().x, graphics->getTextureSize().y * graphics->getSpriteScale().y);
	deleted = false;
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile, const std::string& animName, bool shouldStartPlay, bool isLoop)
{
	graphics = std::make_shared<SpriteSheetComponent>(spriteSheetFile, animName, shouldStartPlay, isLoop);
	isSpriteSheet = true;
	addComponent(graphics);
	//set boxsize of the collider 
	if(getColliderComponent() != nullptr)
		getColliderComponent()->setBoxSize(graphics->getTextureSize().x * graphics->getSpriteScale().x, graphics->getTextureSize().y * graphics->getSpriteScale().y);

}


void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
}



const Vector2f& Entity::getPosition()
{
	return *position->getPosition();
}

const bool Entity::hasComponent(Bitmask componentBits)
{
	return componentSet.contains(componentBits);
}

std::shared_ptr<TTLComponent> Entity::getTTLComponent()
{
	return nullptr;
}

std::shared_ptr<InputComponent> Entity::getInputComponent()
{
	return nullptr;
}

std::shared_ptr<VelocityComponent> Entity::getVelocityComponent()
{
	return nullptr;
}

std::shared_ptr<PositionComponent> Entity::getPositionComponent()
{
	return position;
}

std::shared_ptr<GraphicsComponent> Entity::getGraphicsComponent()
{
	return graphics;
}

std::shared_ptr<ColliderComponent> Entity::getColliderComponent()
{
	return nullptr;
}

std::shared_ptr<LogicComponent> Entity::getLogicComponent()
{
	return nullptr;
}