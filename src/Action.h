#pragma once

namespace sm
{
	class Action
	{
	public:
		typedef unsigned int IdType;

		Action(void);
		~Action(void);

		IdType getId(void) const { return mId; }

	private:
		static IdType sCurrentId;
		IdType mId;
	};
}