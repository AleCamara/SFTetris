#pragma once

#include <string>

namespace sm
{
	class Action
	{
	public:
		typedef unsigned int IdType;

		Action(const std::string&);
		~Action(void) {}

		IdType getId(void) const { return mId; }
		std::string getString(void) const { return mString; }

		void add(void);

	private:
		static IdType sCurrentId;
		IdType mId;
		std::string mString;
	};
}