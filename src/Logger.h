#pragma once

#include <sstream>

namespace sm
{
	class Logger
	{
	public:
		Logger(void);
		~Logger(void) {}

		std::stringstream& getBuffer(void);
		void clearBuffer(void);

		void setDebugLevel(unsigned int level) { mLevel = level; }
		unsigned int getDebugLevel(void) { return mLevel; }

		void info(void);
		void warn(void);
		void error(void);
		void debug(unsigned int level);

	private:
		unsigned int mLevel;
		std::stringstream mBuffer;

		Logger(const Logger&) {}
		Logger& operator=(const Logger&) {}
	};
}