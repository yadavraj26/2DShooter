#pragma once
#include "../../include/entities/Entity.h"
#include "Observer.h"

class Subject
{
public:

	~Subject()
	{
		//observer->removeSubject(*this);
	}

	void assignObserver(std::shared_ptr<Observer> observerRef)
	{
		Subject::observer = observerRef;
		
	}

	/*
	void removeObserver()
	{
		observer = nullptr;
	}*/

protected:
	void notify(Entity* entityRef, EventID eventRef)
	{
		observer->onNotify(entityRef, eventRef);
	}

private:
	std::shared_ptr<Observer> observer;
	
};