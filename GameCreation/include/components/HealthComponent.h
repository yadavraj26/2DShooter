#pragma once
#include "Components.h"
class HealthComponent:public Component
{
public:
	HealthComponent(int startHealth, int max):health(startHealth), maxHealth(max){}
	int getHealth() { return health; }
	void changeHealth(int change) { health += change; if (health > maxHealth)health = maxHealth; if (health < 0)health = 0; }
	ComponentID getID() { return ComponentID::Health; }
protected:
	int health, maxHealth;
};