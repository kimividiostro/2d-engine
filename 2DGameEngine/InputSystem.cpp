#include "InputSystem.h"
#include"World.h"

void InputSystem::update()
{
	for (auto command : m_world.m_dependencies.m_inputManager->getCommandsSinceLastFrame()) 
	{
		if (command.m_type == START) 
		{
			switch (command.m_name)
			{
				case JUMP:
				for (auto& player : m_world.view<Player>()) 
				{
					m_world.add<JumpRequest>(player, {});
				}
				break;
			}
		}
		
		else 
		{
			switch (command.m_type) 
			{

			}
		}
	}
}
