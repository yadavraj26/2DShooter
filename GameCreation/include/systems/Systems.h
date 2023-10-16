#pragma once
#include"../utils/Bitmask.h"
#include "../entities/Entity.h"

class Game;
class Entity;

class System
{
public:
	virtual void update(Game* gameRef, Entity* entityRef, float elapsed) = 0;
	virtual void draw(Game* gameRef, Entity* entityRef, Window* windowRef) = 0;
	bool validate(Entity* entityRef) { return entityRef->hasComponent(componentMask); }
protected:
	Bitmask componentMask;
};

class TTLSystem:public System
{
public:
	TTLSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef){}
};

class InputSystem :public System
{
public:
	InputSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef) {}
};

class MovementSystem : public System
{
public:
	MovementSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef) {}
};

class GraphicsSystem : public System
{
public:
	GraphicsSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef);
};

class ColliderSystem : public System
{
public:
	ColliderSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef) {}
};

class PrintDebugSystem : public System
{
public:
	PrintDebugSystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef);
};

class GameplaySystem : public System
{
public:
	GameplaySystem();
	void update(Game* gameRef, Entity* entityRef, float elapsed);
	void draw(Game* gameRef, Entity* entityRef, Window* windowRef){}
};