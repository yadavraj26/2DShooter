#pragma once
#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include"../../include/components/VelocityComponent.h"
#include"../../include/components/GraphicsComponent.h"
#include"../../include/components/HealthComponent.h"
#include"../../include/components/ColliderComponet.h"
#include"../../include/components/PlayerStateComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER),  collider(std::make_shared<ColliderComponent>())
{
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocity);
	playerInputHandler = std::make_shared<PlayerInputComponent>();
	addComponent(playerInputHandler);
	health = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	addComponent(health);
	logicComp = std::make_shared<PlayerStateComponent>();
	playerState= std::dynamic_pointer_cast<PlayerStateComponent>(logicComp);
	addComponent(logicComp);
	addComponent(collider);
}

Player::~Player() {}



/*void Player::draw(Window* window)
{
	//collider->draw(window);
	//Entity::draw(window);
}*/



void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = graphics->getSpriteScale();
	sf::Vector2u textureSize = graphics->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	setPosition(x + cntrFactorX, y + cntrFactorY);

	velocity->setVelocity(0.f, 0.f);
}

void Player::addPotion(int totalNoPotions)
{
	potionsCount++;
	if (potionsCount >= totalNoPotions)
	{
		notify(this, EventID::PotionMaster);
	}
}

