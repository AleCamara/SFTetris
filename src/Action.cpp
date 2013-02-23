#include "Action.h"

namespace sm
{
	Action::IdType Action::sCurrentId = 0;

	Action::Action(void)
	{
		mId = sCurrentId++;
	}


	Action::~Action(void)
	{
	}
}