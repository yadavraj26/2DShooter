#pragma once
#include"../../include/core/Command.h"
#include"../../include/core/Game.h"
#include"../../include/components/VelocityComponent.h"
#include"../../include/entities/Player.h"
#include"../../include/components/PlayerStateComponent.h"

void MoveRightCommand::execute(Game& gameRef)
{
	gameRef.getPlayer()->getVelocityComp()->setVelocity(1.0f, gameRef.getPlayer()->getVelocityComp()->getVelocity().y);
}

void MoveLeftCommand::execute(Game& gameRef)
{
	gameRef.getPlayer()->getVelocityComp()->setVelocity(-1.0f, gameRef.getPlayer()->getVelocityComp()->getVelocity().y);
}

void MoveUpCommand::execute(Game& gameRef)
{
	gameRef.getPlayer()->getVelocityComp()->setVelocity(gameRef.getPlayer()->getVelocityComp()->getVelocity().x, -1.f);
}

void MoveDownCommand::execute(Game& gameRef)
{
	gameRef.getPlayer()->getVelocityComp()->setVelocity(gameRef.getPlayer()->getVelocityComp()->getVelocity().x,1.f);
}

void AttackCommand::execute(Game& gameRef)
{
	if (!gameRef.getPlayer()->getPlayerStateComp()->isAttacking() && !gameRef.getPlayer()->getPlayerStateComp()->isShouting())
		gameRef.getPlayer()->getPlayerStateComp()->setAttacking(true);
}

void ShoutCommand::execute(Game& gameRef)
{
	if(!gameRef.getPlayer()->getPlayerStateComp()->isShouting() && !gameRef.getPlayer()->getPlayerStateComp()->isAttacking())
		gameRef.getPlayer()->getPlayerStateComp()->setShouting(true);
}