
#pragma once
#include"../../include/components/InputComponent.h"
#include "../../include/core/InputHandler.h"
#include"../../include/core/Command.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Game.h"
#include"../../include/components/VelocityComponent.h"
#include"../../include/entities/Player.h"

PlayerInputComponent::PlayerInputComponent()
{
	pIH = std::make_shared<PlayerInputHandler>();
}



std::vector<std::shared_ptr<Command>> PlayerInputComponent::retreiveCommands()
{
	return pIH->handlePlayerInput();
}


