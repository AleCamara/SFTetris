#pragma once

#include "State.h"

namespace sm
{
	class MenuStage: public State
	{
	public:
		MenuStage(void) {}
		virtual ~MenuStage(void) {}

		virtual void init(void);
	};
}