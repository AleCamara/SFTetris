#include "State.h"

namespace sm
{
	State::IdType State::sCurrentId = 0;

	State::State(void)
	{
		mId = sCurrentId++;
	}

	State::~State(void)
	{
	}
}