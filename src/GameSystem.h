#pragma once

namespace sm
{
	class GameSystem
	{
	public:
		GameSystem(void) {}
		virtual ~GameSystem(void) {}

		virtual void init(void) = 0;
		virtual void quit(void) = 0;
	};
}