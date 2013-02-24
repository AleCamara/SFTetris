#include "MenuStage.h"

#include "Game.h"
#include "Block.h"

namespace sm
{
	void MenuStage::init(void)
	{
		Game::instance()->getLogger()->getBuffer() << "MenuStage::init(void) called";
		Game::instance()->getLogger()->debug(5);

		for(int k=0; k<100; k++)
		{
			addEntity(new Block());
		}
	}
}