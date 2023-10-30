#pragma once
#include"../../include/graphics/Window.h"
#include"../../include/graphics/SpriteSheet.h"
#include"../../include/graphics/AnimDirectional.h"
#include"Components.h"
#include<exception>

class Game;
class Entity;

//when more graphic type adds enum can be used to represent its type. Eg skeleteal mesh
enum class GraphicsType
{
	SimpleSprite = 0,
	SpriteSheet = 1
};

class GraphicsComponent: public Component
{
public:
	~GraphicsComponent() {};
	virtual const sf::Vector2f& getSpriteScale() = 0;
	virtual const sf::Vector2u& getTextureSize() = 0;
	virtual void setSpritePosition(float x, float y) = 0;
	//virtual void init(const std::string& filename) = 0;
	virtual void update(Entity& entityRef, float elapsed) = 0;
	virtual void draw(Window* windowRef) = 0;
	virtual const Direction& getSpriteDirection() = 0;
	virtual AnimBase& getCurrentAnim() = 0;
	virtual void setAnimation(const std::string& animName, bool startPlay, bool isLoop) = 0;
	virtual int getCurrentAnimFrame() = 0;
	virtual void setSpriteDirection(Direction dir) = 0;

	virtual sf::Sprite& getSprite()=0;
	virtual SpriteSheet* getSpriteSheet() = 0;

	ComponentID getID() { return ComponentID::Graphics; }
	GraphicsType graphicsType;

};
class SpriteSheetComponent:public GraphicsComponent
{
public:
	SpriteSheetComponent(const std::string& filename, const std::string& animName, bool startPlay, bool isLoop);

	void update(Entity& entityRef, float elapsed) override;
	void draw(Window* windowRef) override;

	const sf::Vector2f& getSpriteScale() override { return animSprite.getSpriteScale(); }
	const sf::Vector2u& getTextureSize() override { return animSprite.getSpriteSize();}
	void setSpritePosition(float x, float y) override { animSprite.getSprite().setPosition(x, y); }
	
	const Direction& getSpriteDirection() override { return animSprite.getSpriteDirection(); }
	AnimBase& getCurrentAnim()override { return *animSprite.getCurrentAnim(); }
	void setAnimation(const std::string& animName, bool startPlay, bool isLoop) override { animSprite.setAnimation(animName, startPlay, isLoop); }
	int getCurrentAnimFrame()override { return getCurrentAnim().getCurrentFrame(); }
	void setSpriteDirection(Direction dir) override { animSprite.setSpriteDirection(dir); }

	sf::Sprite& getSprite()override { return animSprite.getSprite(); }
	SpriteSheet* getSpriteSheet()override { return &animSprite; }

	ComponentID getID() { return ComponentID::Graphics; }

private:
	SpriteSheet animSprite;
};
class SimpleSpriteComponent :public GraphicsComponent
{
public:
	SimpleSpriteComponent(const std::string& filename, float scale);
	
	void update(Entity& gameRef, float elapsed) override;
	void draw(Window* windowRef) override;

	const sf::Vector2u& getTextureSize() override { return texture.getSize(); }
	const sf::Vector2f& getSpriteScale() override { return sprite.getScale(); }
	void setSpritePosition(float x, float y) override { return sprite.setPosition(x, y); }

	const Direction& getSpriteDirection() override { return Direction::Left; }
	AnimBase& getCurrentAnim()override { throw; }
	void setAnimation(const std::string& animName, bool startPlay, bool isLoop) override { }
	int getCurrentAnimFrame()override { return 0; }
	void setSpriteDirection(Direction dir) override {  }

	sf::Sprite& getSprite()override { return sprite; }
	SpriteSheet* getSpriteSheet()override { return nullptr; }
	
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
};