#pragma once

#include <map>
#include <vector>
#include <boost\shared_ptr.hpp>
#include "State.h"
#include "Action.h"

namespace sm
{
	class StateMachine: public State
	{
	public:
		typedef std::map<std::pair<std::string, std::string>, std::string> RuleMap;
		typedef std::map<std::string, std::string> RuleForAllMap;
		typedef std::map<std::string, boost::shared_ptr<State>> StateContainerType;
		typedef std::vector<std::string> BleepStack;

		StateMachine(const std::string&);
		~StateMachine(void);

		void addState(const boost::shared_ptr<State>&);
		void addRuleForAll(const std::string&, const std::string&);
		void addRule(const std::string&, const std::string&, const std::string&);

		virtual void init(void) {}
		virtual void update(void);
		virtual void quit(void);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		std::string mCurrentState;
		RuleMap mRuleMap;
		RuleForAllMap mRuleForAllMap;
		StateContainerType mStates;
		BleepStack mBleepStack;

		void switchState(const std::string&, const std::string&);
		void popBleepState(void);
		bool checkStateId(const std::string&) const;
	};
}