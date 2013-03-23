#include "TitleState.h"

#include "Game.h"
#include "InputSystem.h"
#include "Action.h"
#include "Logger.h"
#include "TitleImage.h"

namespace sm
{
	TitleState::TitleState(void): State("title")
	{
	}

	TitleState::~TitleState(void)
	{
	}

	void TitleState::init(void)
	{
		init(Action("empty"));
	}

	void TitleState::init(const Action& action)
	{
		addEntity(boost::shared_ptr<Entity>(new TitleImage()));

		Game::instance()->getLogger()->getBuffer() << "TitleState::init()";
		Game::instance()->getLogger()->debug(5);
	}

	void TitleState::update(void)
	{
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::A))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("play")));
		}
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::Escape))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("exit")));
		}
	}

	void TitleState::quit(void)
	{
		Game::instance()->getLogger()->getBuffer() << "TitleState::quit()";
		Game::instance()->getLogger()->debug(5);
	}
}