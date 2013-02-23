#include "Game.h"
#include "MenuStage.h"

int main(int argc, char *argv[])
{
	sm::Game::instance()->getLogger()->setDebugLevel(5);
	sm::Game::instance()->setStage(new sm::MenuStage());
	sm::Game::instance()->loop();

	return 0;
}