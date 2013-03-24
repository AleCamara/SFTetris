#include "StateMachine.h"

#include "Game.h"

namespace sm
{
	StateMachine::StateMachine(const std::string& id)
		: State(id), mCurrentState(), mRuleMap(), mRuleForAllMap(), mStates()
		, mBleepStack()
	{
	}

	StateMachine::~StateMachine(void)
	{
	}

	void StateMachine::addState(const boost::shared_ptr<State>& state)
	{
		if(mStates.find(state->getId()) != mStates.end())
		{
			throw std::invalid_argument("Already exists a state with that state Id.");
		}

		mStates.insert(StateContainerType::value_type(state->getId(),
			boost::shared_ptr<State>(state)));

		// if there's no valid current state use this one
		if(!checkStateId(mCurrentState))
		{
			mCurrentState = state->getId();
			state->init();
		}
	}

	void StateMachine::addRuleForAll(const std::string& action, const std::string& state)
	{
		if(mRuleForAllMap.find(action) != mRuleForAllMap.end())
		{
			throw std::invalid_argument("Already exists a rule for all with that actionId.");
		}

		mRuleForAllMap.insert(RuleForAllMap::value_type(action, state));
	}

	void StateMachine::addRule(const std::string& action, const std::string& origin,
		const std::string& destination)
	{
		if(mRuleMap.find(RuleMap::key_type(action, origin)) != mRuleMap.end())
		{
			throw std::invalid_argument("Already exists a rule for from that origin state with that actionId.");
		}

		mRuleMap.insert(RuleMap::value_type(RuleMap::key_type(action, origin), destination));
	}

	void StateMachine::update(void)
	{
		if(mStates[mCurrentState])
		{
			// check for triggering action
			const Game::ActionContainer& actions = Game::instance()->getActions();
			Game::ActionContainer::const_iterator action = actions.cbegin();
			RuleMap::const_iterator rule;
			RuleForAllMap::const_iterator ruleForAll;
			for(; action != actions.cend(); ++action)
			{
				// exit action
				if((*action)->getId() == "exit")
				{
					Game::instance()->close();
					break;
				}

				// bleep state "back"
				if((*action)->getId() == "back" && mBleepStack.size() > 0)
				{
					popBleepState();
					continue;
				}

				// bleep state "restart"
				if((*action)->getId() == "restart" && mBleepStack.size() > 0)
				{
					popBleepState();
					if(checkStateId(mCurrentState))
					{
						mStates[mCurrentState]->init();
					}
					continue;
				}

				// specific rules have preference over general rules
				rule = mRuleMap.find(RuleMap::key_type((*action)->getId(), mCurrentState));
				if(rule != mRuleMap.cend())
				{
					// switch state and stop searching actions
					switchState(mCurrentState, rule->second, *(*action));
					break;
				}

				// general rules are checked in the end
				ruleForAll = mRuleForAllMap.find((*action)->getId());
				if(ruleForAll != mRuleForAllMap.cend())
				{
					// switch state and stop searching actions
					switchState(mCurrentState, ruleForAll->second, *(*action));
					break;
				}
			}

			// check bleep first
			if(mBleepStack.size() > 0)
			{
				mStates[mBleepStack[mBleepStack.size()-1]]->update();
			}
			else
			{
				mStates[mCurrentState]->update();
			}
		}
	}

	void StateMachine::quit(void)
	{
		// empty the bleep stack
		while(mBleepStack.size() > 0)
		{
			mStates[mBleepStack.at(mBleepStack.size()-1)]->quit();
			mBleepStack.pop_back();
		}

		// quit current state
		if(mStates[mCurrentState])
		{
			mStates[mCurrentState]->quit();
		}
	}

	void StateMachine::draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		// draw current state and then the bleep states in inverse order
		if(checkStateId(mCurrentState))
		{
			mStates.at(mCurrentState)->draw(target, state);
		}
		if(mBleepStack.size() > 0)
		{
			for(int i=0; i<(int) mBleepStack.size(); ++i)
			{
				mStates.at(mBleepStack.at(i))->draw(target, state);
			}
		}
	}

	void StateMachine::switchState(const std::string& origin, const std::string& destination,
		const Action& action)
	{
		if(checkStateId(origin) && checkStateId(destination))
		{
			if(!mStates[destination]->isBleep())
			{
				mStates.at(origin)->quit();
				mCurrentState = destination;
				mBleepStack.clear();
			}
			else
			{
				mBleepStack.push_back(destination);
			}
			mStates.at(destination)->init(action);
		}
	}

	void StateMachine::popBleepState(void)
	{
		if(mBleepStack.size() > 0 && checkStateId(mBleepStack.at(mBleepStack.size()-1)))
		{
			mStates.at(mBleepStack.at(mBleepStack.size()-1))->quit();
			mBleepStack.pop_back();
		}
	}

	bool StateMachine::checkStateId(const std::string& id) const
	{
		return (mStates.find(id) != mStates.cend());
	}
}