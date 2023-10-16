#pragma once
#include "Components.h"
class Game;
class Entity;
class LogicComponent:public Component
{
public:
	virtual void update(Game* gameRef, Entity* entityRef, float elapsed) = 0;
	ComponentID getID() { return ComponentID::Logic; }
};