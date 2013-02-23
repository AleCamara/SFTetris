#include "Logger.h"

#include <iostream>

namespace sm
{
	Logger::Logger(void): mLevel(0), mBuffer()
	{
	}

	std::stringstream& Logger::getBuffer(void)
	{
		return mBuffer;
	}

	void Logger::clearBuffer(void)
	{
		mBuffer.str(std::string());
	}

	void Logger::info(void)
	{
		std::cout << "(II) " << mBuffer.str() << std::endl;
		clearBuffer();
	}

	void Logger::warn(void)
	{
		std::cout << "(WW) " << mBuffer.str() << std::endl;
		clearBuffer();
	}

	void Logger::error(void)
	{
		std::cout << "(EE) " << mBuffer.str() << std::endl;
		clearBuffer();
	}

	void Logger::debug(unsigned int level)
	{
		if(level <= mLevel)
		{
			std::cout << "(DD) " << mBuffer.str() << std::endl;
		}
		clearBuffer();
	}
}