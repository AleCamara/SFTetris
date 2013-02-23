#include "MenuStage.h"

#include "Game.h"

namespace sm
{
	void MenuStage::update(void)
	{
		Game::instance()->getLogger()->getBuffer() << "Game stage has been updated.";
		Game::instance()->getLogger()->debug(5);
	}
}