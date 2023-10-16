#pragma once
#include "../utils/Vector2.h"
#include"Components.h"

class Entity;
class VelocityComponent:public Component
{
public:
	VelocityComponent(float speedVal = 1.f):  speed (speedVal){ }
	void setVelocity(float x, float y) { velocityDirection.x = x; velocityDirection.y = y; }
	const Vector2f& getVelocity()const { return velocityDirection; }
	const float getSpeed()const { return speed; }
	ComponentID getID() { return ComponentID::Velocity; }
private:
	Vector2f velocityDirection;
	float speed;
};