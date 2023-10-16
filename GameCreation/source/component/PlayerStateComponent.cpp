#pragma once
#include"../../include/sound/Audio.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Fire.h"
//#include"../../include/entities/Entity.h"
#include"../../include/entities/Player.h"

#include "../../include/entities/StaticEntities.h"

#include"../../include/entities/EntityPool.h"


#include"../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include"../../include/Service/Locator.h"
//#include "../../include/entities/EntityPool.h"


PlayerStateComponent::PlayerStateComponent():attacking(false), shouting(false), wood(0), shootCooldown(0), noOfShouts(0)
{
	plActionAudioService = Locator::getAudioService(AudioObjectID::PlayerAction);
}

void PlayerStateComponent::update(Game* gameRef, Entity* entityRef, float elapsed)
{

	//set animation for the player
	Player& pl = dynamic_cast<Player&>(*entityRef);
	if (isAttacking())
	{
		entityRef->getGraphicsComponent()->setAnimation("Attack", true, false);
		if (pl.getGraphicsComponent()->getCurrentAnimFrame() == 2)
		{
			plActionAudioService->playSound(AudioID::Attack);
		}
	}
	else if (isShouting())
		entityRef->getGraphicsComponent()->setAnimation("Shout", true, false);
	else if (pl.getVelocityComp()->getVelocity().magnitude() != 0.0f)
	{
		pl.getGraphicsComponent()->setAnimation("Walk", true, true);
		if (pl.getVelocityComp()->getVelocity().x > 0)
			pl.getGraphicsComponent()->setSpriteDirection(Direction::Right);
		else if (pl.getVelocityComp()->getVelocity().x < 0)
			pl.getGraphicsComponent()->setSpriteDirection(Direction::Left);
	}
	else if (pl.getVelocityComp()->getVelocity().magnitude() == 0.0f)
		pl.getGraphicsComponent()->setAnimation("Idle", true, true);

	//shooting animation and logic
	if (shootCooldown > 0.0f)
		shootCooldown -= elapsed;

	if (isShouting() && pl.getGraphicsComponent()->getCurrentAnim().isInAction() &&
		pl.getGraphicsComponent()->getCurrentAnimFrame() == 2 && wood >= shootingCost && shootCooldown <= 0.0f)
	{

		//std::shared_ptr<Fire> fireEntity = std::make_shared<Fire>();

		std::shared_ptr<Fire> fireEntity = gameRef->firePool->getEntity();

		if (fireEntity != nullptr)
		{
			//auto fireEntity = firePool.getEntity();
			Vector2f pos{ pl.getPosition().x + pl.getGraphicsComponent()->getTextureSize().x * 0.5f,
							pl.getPosition().y + pl.getGraphicsComponent()->getTextureSize().y * 0.5f };
			fireEntity->setPosition(pos.x, pos.y);
			fireEntity-> init("img/fire.png", 1.0f);
			
			Vector2f vel(fireSpeed, 0.f);
			if (pl.getGraphicsComponent()->getSpriteDirection() == Direction::Left)
				vel.x = vel.x * -1.0f;
			fireEntity->getVelocityComponent()->setVelocity(vel.x, vel.y);

			std::cout << fireEntity->count;
			gameRef->addEntity(fireEntity);
			addWood(-shootingCost);

			
			plActionAudioService->playSound(AudioID::Shout);
			noOfShouts++;
			if (noOfShouts == 5)
			{
				notify(entityRef, EventID::Loudest);
			}
		}
		else
		{
			std::cout << "wooahh!! Hold UP Rambo! Give some reloading time ";
		}
		shootCooldown = shootCooldownTime;
	}
	



//		  If we are attacking but the current animation is no longer playing, set the attacking flag to false.
//        The same needs to be done for "shouting".
	if (attacking && !(pl.getGraphicsComponent()->getCurrentAnim().isPlaying()))
		attacking = false;
	if (shouting && !(pl.getGraphicsComponent()->getCurrentAnim().isPlaying()))
		shouting = false;


}



void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}