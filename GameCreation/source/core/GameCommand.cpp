#include"../../include/core/Game.h"
#include "../../include/core/Command.h"

void PauseCommand::execute(Game& gameRef)
{
	gameRef.togglePause();
}

void InputSwapCommand::execute(Game& gameRef)
{
	gameRef.changeInput();
}