#include"../../include/components/GraphicsComponent.h"
#include"SFML/Graphics/Sprite.hpp"
#include"../../include/utils/Vector2.h"
#include "../../include/entities/Entity.h"
#include<memory>
SpriteSheetComponent::SpriteSheetComponent(const std::string& filename, const std::string& animName, bool startPlay, bool isLoop) 
{
	animSprite.loadSheet(filename);
	animSprite.setAnimation(animName, startPlay, isLoop);
	graphicsType = GraphicsType::SpriteSheet;
}

SimpleSpriteComponent::SimpleSpriteComponent(const std::string& filename, float scale)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	graphicsType = GraphicsType::SimpleSprite;
}




void SimpleSpriteComponent::update(Entity& entityRef, float elapsed)
{
	setSpritePosition(entityRef.getPosition().x, entityRef.getPosition().y);
}

void SpriteSheetComponent::update(Entity& entityRef, float elapsed)
{
	setSpritePosition(entityRef.getPosition().x, entityRef.getPosition().y);
	animSprite.update(elapsed);
}

void SpriteSheetComponent::draw(Window* windowRef)
{
	windowRef->draw(animSprite.getSprite());
}

void SimpleSpriteComponent::draw(Window* windowRef)
{
	windowRef->draw(sprite);
}

