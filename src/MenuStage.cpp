#include "MenuStage.h"

#include "Game.h"
#include "Board.h"

namespace sm
{
	void MenuStage::init(void)
	{
		Game::instance()->getLogger()->getBuffer() << "MenuStage::init(void) called";
		Game::instance()->getLogger()->debug(5);

		addEntity(new Board(21, 15));
	}
}