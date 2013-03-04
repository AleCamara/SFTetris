#include "InputSystem.h"

#include "Game.h"

namespace sm
{
	InputSystem::InputSystem(void): mEvents()
	{
	}

	void InputSystem::init(void)
	{
		Game::instance()->setKeyRepeatEnabled(false);
	}

	void InputSystem::quit(void)
	{
	}

	void InputSystem::getEvents(void)
	{
		sf::Event ev;
		while(Game::instance()->pollEvent(ev))
		{
			// close window event
			if(ev.type == sf::Event::Closed ||
			   (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape))
			{
				Game::instance()->close();
			}

			// key pressed event
			if(ev.type == sf::Event::KeyPressed)
			{
				mKey[KeyEventState::Pressed][ev.key.code] = true;
			}

			// key released event
			if(ev.type == sf::Event::KeyReleased)
			{
				mKey[KeyEventState::Released][ev.key.code] = true;
			}
		}
	}

	void InputSystem::clearEvents(void)
	{
		resetKeys();
	}

	bool InputSystem::isKeyPressed(Key key) const
	{
		return mKey[KeyEventState::Pressed][key];
	}

	bool InputSystem::isKeyReleased(Key key) const
	{
		return mKey[KeyEventState::Released][key];
	}

	void InputSystem::resetKeys(void)
	{
		for(int state=0; state<2; ++state)
		{
			for(int key=0; key<Key::KeyCount; ++key)
			{
				mKey[state][key] = false;
			}
		}
	}
}