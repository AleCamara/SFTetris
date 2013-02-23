#pragma once

#include <hash_map>
#include <list>
#include <boost\scoped_ptr.hpp>
#include "State.h"
#include "Action.h"

namespace sm
{
	class StateMachine: State
	{
	public:
		typedef std::hash_map<std::pair<State::IdType, Action::IdType>, State::IdType> ResolvMapType;
		typedef std::list<boost::scoped_ptr<State>> StateContainerType;

		StateMachine(void);
		~StateMachine(void);

		void update(void);

	private:
		State *mCurrentState;
		ResolvMapType mResolvMap;
		StateContainerType mStates;
	};
}