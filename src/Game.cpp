#include "Game.h"

#include <Windows.h>

#include <SFML\Window\Event.hpp>

namespace sm
{
	boost::shared_ptr<Game> Game::sInstance;
	
	const unsigned int Game::FRAMERATE = 60;
	const sf::VideoMode Game::VIDEO_MODE = sf::VideoMode(325, 400);
	const std::string Game::TITLE = std::string("Simple+Fast TETRIS");
	const unsigned int Game::STYLE = sf::Style::Titlebar | sf::Style::Close;

	Game::Game(void): RenderWindow(VIDEO_MODE, TITLE, STYLE), mStage(), mLogger(new Logger()),
		mActions(), mDeltaClock(), mDeltaTime()
	{
		setFramerateLimit(FRAMERATE);

		mMath = boost::shared_ptr<MathSystem>(new MathSystem());
		mInput = boost::shared_ptr<InputSystem>(new InputSystem());
	}

	Game::~Game(void)
	{
		if(mMath)
		{
			mMath->quit();
		}
		if(mInput)
		{
			mInput->quit();
		}
	}

	boost::shared_ptr<Game> Game::instance(void)
	{
		if(!sInstance)
		{
			sInstance = boost::shared_ptr<Game>(new Game());
		}

		return sInstance;
	}

	void Game::setStage(boost::shared_ptr<State> stage)
	{
		if(stage)
		{
			stage->init();
			mStage.swap(stage);
		}
	}

	boost::shared_ptr<InputSystem> Game::getInput(void)
	{
		return mInput;
	}

	boost::shared_ptr<MathSystem> Game::getMath(void)
	{
		return mMath;
	}

	boost::shared_ptr<Logger> Game::getLogger(void)
	{
		return mLogger;
	}
	
	void Game::addAction(const boost::shared_ptr<Action>& action)
	{
		mActions.push_back(boost::shared_ptr<Action>(action));
	}

	const Game::ActionContainer& Game::getActions(void) const
	{
		return mActions;
	}

	sf::Time Game::getDeltaTime(void) const
	{
		return mDeltaTime;
	}

	void Game::init(void)
	{
		mMath->init();
		mInput->init();
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

			clear(sf::Color(0x20, 0x20, 0x20, 255));
			if(mStage)
			{
				mStage->update();
				draw(*mStage.get());
			}
			display();

			mActions.clear();

			mDeltaTime = mDeltaClock.restart();
		}
	}

}