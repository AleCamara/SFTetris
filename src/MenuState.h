#pragma once

#include "State.h"

namespace sm
{
	class MenuState: public State
	{
	public:
		MenuState(void);
		virtual ~MenuState(void) {}

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);
	};
}