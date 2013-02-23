#pragma once

namespace sm
{
	class IMutable
	{
	public:
		virtual ~IMutable() {}
		virtual void update(void) = 0;
	};
}