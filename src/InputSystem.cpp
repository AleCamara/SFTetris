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

	void InputSystem::update(void)
	{
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

			// lost focus
			if(ev.type == sf::Event::LostFocus)
			{
				Game::instance()->pause();
			}

			// gained focus
			if(ev.type == sf::Event::GainedFocus)
			{
				Game::instance()->unpause();
			}

			// key pressed event
			if(ev.type == sf::Event::KeyPressed)
			{
				mKey[Pressed][ev.key.code] = true;
			}

			// key released event
			if(ev.type == sf::Event::KeyReleased)
			{
				mKey[Released][ev.key.code] = true;
			}
		}
	}

	void InputSystem::clearEvents(void)
	{
		resetKeys();
	}

	bool InputSystem::isKeyPressed(Key key) const
	{
		return mKey[Pressed][key];
	}

	bool InputSystem::isKeyReleased(Key key) const
	{
		return mKey[Released][key];
	}

	void InputSystem::resetKeys(void)
	{
		for(int state=0; state<2; ++state)
		{
			for(int key=0; key<sf::Keyboard::KeyCount; ++key)
			{
				mKey[state][key] = false;
			}
		}
	}
}