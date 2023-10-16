#pragma once
//#include "Game.h"
//#include "Command.h"
#include<memory>
#include<map>
#include<vector>
#include"SFML/Graphics.hpp"

class Command;
class PauseCommand;
class Game;

enum class CommandID
{
	UNDEFINED=-1,
	MoveUp=0,
	MoveDown=1,
	MoveLeft=2,
	MoveRight=3,
	Attack=4,
	Shout=5
};

class InputHandler
{
public:
	InputHandler();
	std::shared_ptr<Command> handleInput();
private:
	std::shared_ptr<Command> pauseCommand;
	std::shared_ptr<Command> inputSwapCommand;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();
	std::vector<std::shared_ptr<Command>>& handlePlayerInput();
	std::shared_ptr<Command> getCommand(CommandID command);
	void changeMovementKeys();

protected:
	void changeKeyBinding(std::shared_ptr<Command> commandToChange, sf::Keyboard::Key key) { keyBinds[commandToChange] = key; }
	
private:
	std::shared_ptr<Command> moveRight;
	std::shared_ptr<Command> moveLeft;
	std::shared_ptr<Command> moveUp;
	std::shared_ptr<Command> moveDown;
	std::shared_ptr<Command> attackAction;
	std::shared_ptr<Command> shoutAction;
	std::vector<std::shared_ptr<Command>> keysPressed;

	std::map<std::shared_ptr<Command>, sf::Keyboard::Key> keyBinds; // , arrowKeys;
	bool isArrowKeys=false;
	
};
