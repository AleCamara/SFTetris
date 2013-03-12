#include "MenuState.h"

#include "Game.h"
#include "Action.h"
#include "InputSystem.h"
#include "Logger.h"
#include "MenuImage.h"

namespace sm
{
	MenuState::MenuState(void): State("menu", true)
	{
	}

	void MenuState::init(void)
	{
		addEntity(boost::shared_ptr<Entity>(new MenuImage()));
		Game::instance()->getLogger()->getBuffer() << "MenuState::init()";
		Game::instance()->getLogger()->debug(5);
	}

	void MenuState::update(void)
	{
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::A))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("back")));
		}
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::S))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("gotitle")));
		}
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::Escape))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("exit")));
		}
	}

	void MenuState::quit(void)
	{
		Game::instance()->getLogger()->getBuffer() << "MenuState::quit()";
		Game::instance()->getLogger()->debug(5);
	}
}