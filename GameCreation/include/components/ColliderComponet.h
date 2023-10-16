#pragma once
#include<SFML/System/Vector2.hpp>
#include "../utils/Rectangle.h"
#include "Components.h"



class ColliderComponent : public Component
{
public:
	ColliderComponent():boxSize(0.5f,0.5f) {}
	void setBoxSize(float x, float y) { boxSize.x = x; boxSize.y = y; }
	void setBoundingBox(Vector2f topLeft, Vector2f bottomRight) { boundingBox.setTopLeft(topLeft); boundingBox.setBottomRight(bottomRight); }
	
	void draw(Window* window) { window->draw(boundingBox.getDrawableRect()); }
	void update(Entity& entityRef, float elapsedTime)
	{
		// update bounding box for moving entities
		//setBoundingBox(entityRef.getPosition(), Vector2f(entityRef.getPosition().x + boxSize.x, entityRef.getPosition().y + boxSize.y));
	}

	bool intersects(std::shared_ptr<ColliderComponent> otherComponent) { return boundingBox.intersects(otherComponent->getBoundingBox()); }

	Rectangle& getBoundingBox() { return boundingBox; }
	const sf::Vector2f& getBoxSize()const { return boxSize; }

	ComponentID getID() { return ComponentID::Collider; }

private:
	Rectangle boundingBox;
	sf::Vector2f boxSize;
};