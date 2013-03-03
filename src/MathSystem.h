#pragma once

#include "GameSystem.h"

namespace sm
{
	class MathSystem: public GameSystem
	{
	public:
		MathSystem(void) {}
		virtual ~MathSystem(void) {}

		virtual void init(void);
		virtual void quit(void);

		float getRandomNumber(void);
		int getRandomInteger(void);
	};
}