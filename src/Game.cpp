#include "Game.h"

#include <Windows.h>

#include <SFML\Window\Event.hpp>

namespace sm
{
	Game *Game::sInstance = 0;
	
	const unsigned int Game::FRAMERATE = 60;
	const sf::VideoMode Game::VIDEO_MODE = sf::VideoMode(300, 400);
	const std::string Game::TITLE = std::string("Simple+Fast TETRIS");
	const unsigned int Game::STYLE = sf::Style::Titlebar | sf::Style::Close;

	Game::Game(void): RenderWindow(VIDEO_MODE, TITLE, STYLE), mStage(), mLogger(new Logger())
	{
		setFramerateLimit(FRAMERATE);
	}

	Game::~Game(void)
	{
		if(sInstance)
		{
			delete sInstance;
		}
	}

	Game *Game::instance(void)
	{
		if(!sInstance)
		{
			sInstance = new Game();
		}

		return sInstance;
	}

	void Game::setStage(State *stage)
	{
		mStage.reset(stage);
	}

	Logger *Game::getLogger(void)
	{
		return mLogger.get();
	}

	void Game::loop(void)
	{
		while(isOpen())
		{
			
			sf::Event ev;
			while (pollEvent(ev))
			{
				// close window event
				if(ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape))
				{
					close();
				}
			}

			if(mStage)
			{
				mStage->update();
			}

			clear();
			display();
		}
	}

}