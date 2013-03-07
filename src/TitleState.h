#pragma once

#include "State.h"

namespace sm
{
	class TitleState: public State
	{
	public:
		TitleState(void);
		virtual ~TitleState(void);

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);
	};
}