#pragma once

enum class ComponentID
{
	UNDEFINED = -1,
	Input=1,
	Position=2,
	Velocity=3,
	Collider=4,
	Graphics=5,
	PlayerState=6,
	Logic=7,
	Health=8,
	TTL=9,
	Audio=10
};

class Component
{
public:
	virtual ComponentID getID()=0;
};