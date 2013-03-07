#include "Game.h"
#include "MenuStage.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
	sm::Game::instance()->init();
	sm::Game::instance()->getLogger()->setDebugLevel(5);
	sm::Game::instance()->addState(boost::shared_ptr<sm::State>(new sm::MenuStage()));
	sm::Game::instance()->loop();

	sm::Game::instance()->getLogger()->getBuffer() << "Press any key to exit.";
	sm::Game::instance()->getLogger()->info();
	getchar();

	return 0;
}