#pragma once

#include "State.h"

namespace sm
{
	class GameOverState: public State
	{
	public:
		GameOverState(void);
		virtual ~GameOverState(void);

		virtual void init(void);
		virtual void init(const Action&);
		virtual void update(void);
	};
}