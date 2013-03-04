#pragma once

#include <vector>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "GameSystem.h"

namespace sm
{
	class InputSystem: public GameSystem
	{
	public:
		typedef sf::Keyboard::Key Key;

		InputSystem(void);
		virtual ~InputSystem(void) {}

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);

		void getEvents(void);
		void clearEvents(void);

		bool isKeyPressed(Key) const;
		bool isKeyReleased(Key) const;

	private:
		enum KeyEventState
		{
			Pressed,
			Released,
			Count
		};

		typedef std::vector<sf::Event> EventContainer;
		
		EventContainer mEvents;
		bool mKey[KeyEventState::Count][Key::KeyCount];

		void resetKeys(void);
	};
}