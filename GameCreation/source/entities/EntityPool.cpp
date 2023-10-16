//#include"../../include/entities/EntityPool.h"
//#include"../../include/entities/StaticEntities.h"
//#include"../../include/entities/Fire.h"
//
//template <class T>
//EntityPool<T>::EntityPool()
//{
//	firstFree = &pool[0];
//	for (int i = 0; i < std::size(pool) - 1; i++)
//	{
//		std::cout << i<<"\n";
//		pool[i].setNext(&pool[i + 1]);
//	}
//	pool[std::size(pool) - 1].setNext(NULL);
//}
//
//template <class T>
//T* EntityPool<T>::instantiate(const std::string& textureFile, float scale)
//{
//	if (firstFree != nullptr)
//	{
//		firstFree->init(textureFile, scale);
//		return firstFree;
//	}
//}
//
//template <class T>
//void EntityPool<T>::hibernate(T* deleted)
//{
//	deleted->setNext(firstFree);
//	firstFree = deleted;
//}