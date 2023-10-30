#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../utils/Bitmask.h"
#include "../components/Components.h"




using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration
class PositionComponent;
class GraphicsComponent;
class ColliderComponent;
class TTLComponent;
class InputComponent;
class VelocityComponent;
class LogicComponent;

struct EntityPoolData
{
	EntityID id;
	EntityType type;
};

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale);
	void initSpriteSheet(const std::string& spriteSheetFile, const std::string& animName, bool startPlay, bool isLoop);
	//virtual void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { state.data.id = entId; }
	EntityID getID() const { return state.data.id; }
	void setPosition(float x, float y);
	const Vector2f& getPosition();
	
	EntityType getEntityType() const { return state.data.type; }

	//bool isSpriteSheetEntity() const { return isSpriteSheet; }
	//std::shared_ptr<GraphicsComponent> getGraphicsComponent() { return graphics; }

	bool isDeleted() const { return deleted;}
	virtual void deleteEntity() { deleted = true; }



	void setNext(std::shared_ptr<Entity> nextItem)
	{
		state.next = nextItem;
	}

	std::shared_ptr<Entity> getNext() { return state.next; }


	Bitmask getComponentSet() { return componentSet; }

	void addComponent(std::shared_ptr<Component> componentRef) { componentSet.turnOnBit((unsigned int)componentRef->getID()); }
	const bool hasComponent(Bitmask mask);

	virtual std::shared_ptr<TTLComponent> getTTLComponent();
	virtual std::shared_ptr<InputComponent> getInputComponent();
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent();
	virtual std::shared_ptr<PositionComponent> getPositionComponent();
	virtual std::shared_ptr<GraphicsComponent> getGraphicsComponent();
	virtual std::shared_ptr<ColliderComponent> getColliderComponent();
	virtual std::shared_ptr<LogicComponent> getLogicComponent();
	int count = 0;
	
protected:
	//Graphics Function
	/*union Info
	{
		struct Data
		{
			EntityType type;
			EntityID id;
		}data;
		std::shared_ptr<Entity> next;
	}info;*/
	/*EntityType type;
	EntityID id;

	EntityPoolData data;*/

	union State
	{
		EntityPoolData data;
		std::shared_ptr<Entity> next;
		State() : next(){}
		~State(){}
	}state;

	//Position and velocity
	std::shared_ptr<PositionComponent> position;
	//std::shared_ptr<Entity> next;

	//Collision
	

	//Graphics-related variables.
	bool isSpriteSheet;
	std::shared_ptr<GraphicsComponent> graphics;

	/*union
	{
		// State when it's in use.
		struct
		{
			double x, y;
			double xVel, yVel;
		} live;

		// State when it's available.
		std::shared_ptr<Entity> next;
	} state_;*/


private:
	bool deleted;
	Bitmask componentSet;
	
};