#pragma once

#include "GameSystem.h"
#include <map>
#include <SFML\System\Time.hpp>

namespace sm
{
	class MathSystem: public GameSystem
	{
	public:
		MathSystem(void);
		virtual ~MathSystem(void) {}

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);

		float getRandomNumber(void);
		int getRandomInteger(void);

		unsigned int createTimer(void);
		/* Throws std::out_of_range if the key does not exist. */
		void restartTimer(const unsigned int);
		void removeTimer(const unsigned int);
		/* Throws std::out_of_range if the key does not exist. */
		sf::Time getTimeOfTimer(const unsigned int) const;

	private:
		static unsigned int sCurrentId;

		sf::Time mMasterTime;
		std::map<unsigned int, sf::Time> mTimers;

		void createTimerAtKey(const unsigned int);
	};
}