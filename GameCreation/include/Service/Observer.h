#pragma once
#include<iostream>
#include "../../include/entities/Entity.h"
#include"../../include/Service/Subject.h"


enum class EventID
{
	PotionMaster=0,
	Loudest=1
};

class Observer
{
public:
	~Observer()
	{
	
	}

	virtual void onNotify(Entity* entityRef, EventID) =0;

};

class Acheivements : public Observer
{
public:
	void onNotify(Entity* entityRef, EventID eventRef) override
	{
		
		switch (eventRef)
		{
		case EventID::PotionMaster:
			std::cout << "\n\n You are a Potions Master! \n\n\n";
			break;
		case EventID::Loudest:
			std::cout << "\n\n Your enemies fear your Roar! \n\n\n";
			break;
		default:
			break;
		}
	}


};