#pragma once
//#include "InputHandler.h"
class Game;
class InputHandler;
class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Game& gameRef) = 0;
};

class PauseCommand : public Command
{
public:
	void execute(Game& gameRef) override;
};

class InputSwapCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class MoveRightCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class MoveLeftCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class MoveUpCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class MoveDownCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class AttackCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};

class ShoutCommand :public Command
{
public:
	void execute(Game& gameRef) override;
};