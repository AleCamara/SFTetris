#include "MathSystem.h"

#include <cstdlib>
#include <time.h>

namespace sm
{
	void MathSystem::init(void)
	{
		srand(time(0));
	}

	void MathSystem::quit(void) {}

	float MathSystem::getRandomNumber(void)
	{
		return ((float) getRandomInteger()) / ((float) RAND_MAX);
	}

	int MathSystem::getRandomInteger(void)
	{
		return rand();
	}
}
