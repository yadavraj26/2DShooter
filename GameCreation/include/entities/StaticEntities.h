#pragma once
#include "../components/ColliderComponet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponet.h"
#include "Entity.h"
#include<memory>
#include<iostream>


class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION), collider(std::make_shared<ColliderComponent>())
	{
		addComponent(collider);
	}
	~Potion() { std::cout << "deleted"; }



	void init(const std::string& textureFile, float scale) override
	{
		// Call the init() function in Entity to initalize this object
		Entity::init(textureFile,scale);
		state.data.type = EntityType::POTION;
		//  set the sprite location initially top left and bottom right corners of the bounding box for this entity. since there is no update needed 
		graphics->setSpritePosition(getPosition().x, getPosition().y);
		collider->setBoundingBox(getPosition(), Vector2f(getPosition().x + collider->getBoxSize().x, getPosition().y + collider->getBoxSize().y));
	}


	int getHealth() const { return potionHealth;  }
	std::shared_ptr<ColliderComponent> getColliderComponent()override { return collider; }

protected:
	const int potionHealth = 10;

private:
	std::shared_ptr<ColliderComponent> collider;

};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG), collider(std::make_shared<ColliderComponent>())
	{
		addComponent(collider);
		//next = nullptr;
	}
	~Log() {}


	/*void setNext(Log* nextItem)
	{
		next = nextItem;
	}

	Log* getNext() { return next; }*/

	void init(const std::string& textureFile, float scale) override
	{
		state.data.type = EntityType::LOG;
		//Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);
		//  set the sprite location initially top left and bottom right corners of the bounding box for this entity. since there is no update needed 
		graphics->setSpritePosition(getPosition().x, getPosition().y);
		collider->setBoundingBox(getPosition(), Vector2f(getPosition().x + collider->getBoxSize().x, getPosition().y + collider->getBoxSize().y));
	}


	//void draw(Window* window) override {  Entity::draw(window); }

	int getWood() const { return woodAdded; }
	std::shared_ptr<ColliderComponent> getColliderComponent()override { return collider; }


protected:
	const int woodAdded = 15;

private:
	std::shared_ptr<ColliderComponent> collider;
	//Log* next;

};