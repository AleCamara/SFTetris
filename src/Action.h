#pragma once

#include <string>

namespace sm
{
	class Action
	{
	public:
		Action(const std::string&);
		~Action(void) {}

		const std::string& getId(void) const { return mId; }

		void add(void);

	private:
		std::string mId;
	};
}