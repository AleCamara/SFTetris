#include "Game.h"
#include "TitleState.h"
#include "MainState.h"
#include "MenuState.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
	sm::Game::instance()->init();
	sm::Game::instance()->getLogger()->setDebugLevel(5);

	// setup game state machine

	// states
	sm::Game::instance()->addState(boost::shared_ptr<sm::State>(new sm::TitleState()));
	sm::Game::instance()->addState(boost::shared_ptr<sm::State>(new sm::MainState()));
	sm::Game::instance()->addState(boost::shared_ptr<sm::State>(new sm::MenuState()));

	// rules
	sm::Game::instance()->addRule("play", "title", "game");
	sm::Game::instance()->addRule("gomenu", "game", "menu");
	sm::Game::instance()->addRule("gotitle", "game", "title");

	// go for it!
	sm::Game::instance()->loop();

	sm::Game::instance()->getLogger()->getBuffer() << "Press any key to exit.";
	sm::Game::instance()->getLogger()->info();
	getchar();

	return 0;
}