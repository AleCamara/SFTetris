#include "MathSystem.h"

#include <cstdlib>
#include <time.h>
#include "Game.h"

namespace sm
{
	unsigned int MathSystem::sCurrentId = 0;

	MathSystem::MathSystem(void): mMasterTime(), mTimers()
	{
	}

	void MathSystem::init(void)
	{
		srand(time(0));
		mMasterTime = sf::Time();
	}

	void MathSystem::update(void)
	{
		if(!Game::instance()->isPaused())
		{
			mMasterTime += Game::instance()->getDeltaTime();
		}
	}

	void MathSystem::quit(void)
	{
	}

	float MathSystem::getRandomNumber(void)
	{
		return ((float) getRandomInteger()) / ((float) RAND_MAX);
	}

	int MathSystem::getRandomInteger(void)
	{
		return rand();
	}

	unsigned int MathSystem::createTimer(void)
	{
		std::pair<unsigned int, sf::Time> newTimer(sCurrentId++, sf::Time(mMasterTime));
		mTimers.insert(newTimer);
		return newTimer.first;
	}
	
	void MathSystem::restartTimer(const unsigned int key)
	{
		removeTimer(key);
		createTimerAtKey(key);
	}

	void MathSystem::removeTimer(const unsigned int key)
	{
		mTimers.erase(key);
	}

	sf::Time MathSystem::getTimeOfTimer(const unsigned int key) const
	{
		return mMasterTime - mTimers.at(key);
	}

	void MathSystem::createTimerAtKey(const unsigned int key)
	{
		if(mTimers.find(key) == mTimers.end())
		{
			std::pair<unsigned int, sf::Time> newTimer(key, mMasterTime);
			mTimers.insert(newTimer);
		}
	}
}
