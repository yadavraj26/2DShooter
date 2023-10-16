#pragma once
//#include <string>
#include<memory>
#include"Entity.h"
//#include"Fire.h"
//#include"StaticEntities.h"

class Fire;

/*#include<iostream>
#include<array>*/


template <typename T>
constexpr int getSize()
	{
		if (std::is_same_v < T, Fire>)
		{
			return 3;
		}
		return 8;
	}

template <class T>
class EntityPool
{
public:
	EntityPool() {
		//Set the NExt element for all the entities in the pool
		firstFree = std::shared_ptr<T>(&pool[0]);
		for (int i = 0; i < std::size(pool) - 1; i++)
		{
			std::cout << i << "\n";
			pool[i].setNext(std::shared_ptr<T> (&pool[i + 1]));
			pool[i].count = i;
		}
		pool[std::size(pool)-1].setNext(NULL);
	}
	std::shared_ptr<T> getEntity() {
		if (firstFree != nullptr)
		{
			//change first free to nextavailable and return the initial firstFree
			std::shared_ptr<T> temp = firstFree;
			firstFree = std::dynamic_pointer_cast<T> (firstFree->getNext());
			
			
			return temp;
		}
		return firstFree;
	}
	void hibernate(std::shared_ptr<Entity> deleted) {
		//Add the deeted entity on top of the free list
		deleted->setNext(firstFree);
		firstFree = std::dynamic_pointer_cast<T>(deleted);
	}


private:
	T pool[getSize<T>()];
	//T pool[16];
	std::shared_ptr<T> firstFree;
};


/*template <class T>
class PotionPool :public EntityPool
{
public:
	T changeToType(std::shared_ptr<Entity> ent)
	{
		reinterpret_cast<std::shared_ptr<T>> (ent);
	}
};*/


