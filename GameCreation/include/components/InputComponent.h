#pragma once
#include"../../include/core/InputHandler.h"
#include"Components.h"
#include<memory>
//#include"../../include/core/Game.h"
//class PlayerInputHandler;
class Game;
class InputComponent:public Component
{
public:
	~InputComponent() {};
	virtual void update(Game& gameRef) = 0;
	virtual std::vector<std::shared_ptr<Command>> retreiveCommands()=0;
	ComponentID getID() { return ComponentID::Input; }
};

class PlayerInputComponent :public InputComponent
{
public:
	PlayerInputComponent();
	virtual void update(Game& gameRef) override {};
	std::shared_ptr <PlayerInputHandler> getPlayerInputHandler() { return pIH; }
	std::vector<std::shared_ptr<Command>> retreiveCommands();

private:
	std::shared_ptr <PlayerInputHandler> pIH;

};