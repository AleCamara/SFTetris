#include "InputSystem.h"

#include "Game.h"

namespace sm
{
	void InputSystem::init(void)
	{
		Game::instance()->setKeyRepeatEnabled(false);
	}

	void InputSystem::quit(void)
	{
	}

	bool InputSystem::isKeyPressed(Key key) const
	{
		return sf::Keyboard::isKeyPressed(key);
	}
}