#include "GameOverState.h"

#include "Action.h"
#include "GameOverEntity.h"
#include "Game.h"
#include "Logger.h"
#include "InputSystem.h"

namespace sm
{
	GameOverState::GameOverState(void): State("gameover", true)
	{
	}

	GameOverState::~GameOverState(void)
	{
	}

	void GameOverState::init(void)
	{
		init(Action("empty"));
	}

	void GameOverState::init(const Action& action)
	{
		addEntity(boost::shared_ptr<Entity>(new GameOverEntity()));
		Game::instance()->getLogger()->getBuffer() << "GameOverState::init()";
		Game::instance()->getLogger()->debug(5);
	}
	
	void GameOverState::update(void)
	{
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::A))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("restart")));
		}
		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::Escape))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("gotitle")));
		}
	}
}