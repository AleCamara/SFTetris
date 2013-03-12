#pragma once

#include <vector>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "GameSystem.h"

namespace sm
{
	using sf::Keyboard;

	class InputSystem: public GameSystem
	{
	public:
		typedef sf::Keyboard Keyboard;

		InputSystem(void);
		virtual ~InputSystem(void) {}

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);

		void getEvents(void);
		void clearEvents(void);

		bool isKeyPressed(Keyboard::Key) const;
		bool isKeyReleased(Keyboard::Key) const;

	private:
		enum KeyEventState
		{
			Pressed,
			Released,
			KeyEventStateCount
		};

		typedef std::vector<sf::Event> EventContainer;
		
		EventContainer mEvents;
		bool mKey[KeyEventStateCount][sf::Keyboard::KeyCount];

		void resetKeys(void);
		void InputSystem::resetReleased(void);
		void InputSystem::resetPressed(void);
	};
}