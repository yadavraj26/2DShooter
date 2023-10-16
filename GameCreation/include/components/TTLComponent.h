#pragma once
#include"Components.h"
class TTLComponent:public Component
{

public:
	TTLComponent(int time):ttl(time){}
	int getTtl() { return ttl; }
	ComponentID getID() { return ComponentID::TTL; }
	void decreaseTTL(){ if (ttl > 0)ttl--; }
	void resetTTL(int resetTime) { ttl = resetTime; }

private:
	int ttl;
};