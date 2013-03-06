#include "Game.h"

#include <Windows.h>
#include <SFML\System\Time.hpp>
#include "State.h"
#include "Action.h"
#include "Logger.h"
#include "MathSystem.h"
#include "InputSystem.h"
#include "AudioSystem.h"

namespace sm
{
	boost::shared_ptr<Game> Game::sInstance;
	
	const unsigned int Game::FRAMERATE = 60;
	const sf::VideoMode Game::VIDEO_MODE = sf::VideoMode(325, 400);
	const std::string Game::TITLE = std::string("Simple+Fast TETRIS");
	const unsigned int Game::STYLE = sf::Style::Titlebar | sf::Style::Close;

	Game::Game(void): RenderWindow(VIDEO_MODE, TITLE, STYLE), mStage(), mLogger(new Logger()),
		mActions(), mDeltaClock(), mDeltaTime(), mPaused(false)
	{
		setFramerateLimit(FRAMERATE);

		mMath = boost::shared_ptr<MathSystem>(new MathSystem());
		mInput = boost::shared_ptr<InputSystem>(new InputSystem());
		mAudio = boost::shared_ptr<AudioSystem>(new AudioSystem());
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
		if(mAudio)
		{
			mAudio->quit();
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

	boost::shared_ptr<AudioSystem> Game::getAudio(void)
	{
		return mAudio;
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
		mAudio->init();
	}

	void Game::loop(void)
	{
		while(isOpen())
		{
			// system updates
			getMath()->update();
			getInput()->update();
			
			clear(sf::Color(0x20, 0x20, 0x20, 255));
			if(mStage)
			{
				if(!mPaused)
				{
					mStage->update();
				}
				draw(*mStage.get());
			}
			display();

			mActions.clear();

			mDeltaTime = mDeltaClock.restart();
		}

		if(mStage)
		{
			mStage->quit();
		}
	}

	void Game::pause(void)
	{
		mPaused = true;
	}

	void Game::unpause(void)
	{
		mPaused = false;
	}
}