#pragma once

#include "Mutable.h"

namespace sm
{
	class State: public IMutable
	{
	public:
		typedef unsigned int IdType;

		State(void);
		virtual ~State(void);

		IdType getId(void) const { return mId; }

		void update(void) {}

	private:
		static IdType sCurrentId;
		IdType mId;
	};
}