#include"../../include/systems/Systems.h"
#include"../../include/components/InputComponent.h"
#include"../../include/core/Game.h"
#include "../../include/components/VelocityComponent.h"
#include"../../include/core/Command.h"

InputSystem::InputSystem()
{
	componentMask.turnOnBit(static_cast <int>(ComponentID::Input));
	componentMask.turnOnBit(static_cast <int>(ComponentID::Velocity));
}

void InputSystem::update(Game* gameRef, Entity* entityRef, float elapsed)
{
	if (entityRef->getInputComponent() != nullptr && entityRef->getVelocityComponent() != nullptr)
	{
		entityRef->getVelocityComponent()->setVelocity(0.f, 0.f);
		std::vector<std::shared_ptr<Command>> command = entityRef->getInputComponent()->retreiveCommands();
		std::vector<std::shared_ptr<Command>>::iterator it = command.begin();
		while (it < command.end())
		{
			(*it)->execute(*gameRef);
			it++;
		}
	}
}