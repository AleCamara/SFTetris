#include "Action.h"

namespace sm
{
	Action::IdType Action::sCurrentId = 0;

	Action::Action(const std::string& actionString)
		: mString(actionString)
	{
		mId = sCurrentId++;
	}
}