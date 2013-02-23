#include "StateMachine.h"

namespace sm
{
	StateMachine::StateMachine(void): mCurrentState(NULL)
	{
	}

	StateMachine::~StateMachine(void)
	{
	}

	void StateMachine::update(void)
	{
		if(mCurrentState)
		{
			mCurrentState->update();
		}
	}
}