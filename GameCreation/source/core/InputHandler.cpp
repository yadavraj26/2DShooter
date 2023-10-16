#pragma once
#include"../../include/core/InputHandler.h"
#include"../../include/core/Game.h"
#include "../../include/core/Command.h"
//#include<memory>
InputHandler::InputHandler() 
{
	pauseCommand = std::make_shared<PauseCommand>();
	inputSwapCommand = std::make_shared<InputSwapCommand>();
	//pauseCommand = new PauseCommand();
}

std::shared_ptr<Command> InputHandler::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return pauseCommand;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		return inputSwapCommand;
	else return nullptr;
}

PlayerInputHandler::PlayerInputHandler()
{
	moveRight = std::make_shared<MoveRightCommand>();
	moveLeft = std::make_shared<MoveLeftCommand>();
	moveUp = std::make_shared<MoveUpCommand>();
	moveDown = std::make_shared<MoveDownCommand>();
	attackAction = std::make_shared<AttackCommand>();
	shoutAction = std::make_shared<ShoutCommand>();

	keyBinds[moveLeft] = sf::Keyboard::A;
	keyBinds[moveRight] =  sf::Keyboard::D;
	keyBinds[moveUp] =  sf::Keyboard::Key::W;
	keyBinds[moveDown] =  sf::Keyboard::Key::S;
	keyBinds[attackAction] =  sf::Keyboard::Key::Space;
	keyBinds[shoutAction] =  sf::Keyboard::Key::LShift;
}


std::shared_ptr<Command> PlayerInputHandler::getCommand(CommandID command)
{
	switch (command)
	{
	case CommandID::UNDEFINED:
		return nullptr;
	case CommandID::MoveUp:
		return moveUp;
	case CommandID::MoveDown:
		return moveDown;
	case CommandID::MoveLeft:
		return moveLeft;
	case CommandID::MoveRight:
		return moveRight;
	case CommandID::Attack:
		return attackAction;
	case CommandID::Shout:
		return shoutAction;
	default:
		return nullptr;
	}
}


std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handlePlayerInput()
{
	keysPressed.clear();
	std::map<std::shared_ptr<Command>, sf::Keyboard::Key>::iterator it;
	for (it = keyBinds.begin(); it != keyBinds.end(); it++)
	{
		if(sf::Keyboard::isKeyPressed(it->second))
			keysPressed.push_back(it->first);
	}
	return keysPressed;
}

void PlayerInputHandler::changeMovementKeys()
{
	if (isArrowKeys)
	{
		keyBinds[moveUp] = sf::Keyboard::Key::W;
		keyBinds[moveDown] = sf::Keyboard::Key::S;
		keyBinds[moveLeft] = sf::Keyboard::Key::A;
		keyBinds[moveRight] = sf::Keyboard::Key::D;
	}
	else
	{
		keyBinds[moveUp] = sf::Keyboard::Key::Up;
		keyBinds[moveDown] = sf::Keyboard::Key::Down;
		keyBinds[moveLeft] = sf::Keyboard::Key::Left;
		keyBinds[moveRight] = sf::Keyboard::Key::Right;
	}
	isArrowKeys = !isArrowKeys;
}