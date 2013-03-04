#pragma once

#include <SFML\Window\Keyboard.hpp>
#include "GameSystem.h"

namespace sm
{
	class InputSystem: public GameSystem
	{
	public:
		typedef sf::Keyboard::Key Key;

		InputSystem(void) {}
		virtual ~InputSystem(void) {}

		virtual void init(void);
		virtual void quit(void);

		bool isKeyPressed(Key) const;
	};
}