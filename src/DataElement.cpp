#include "DataElement.h"

namespace sm
{
	DataElement::DataElement(const std::string& string): mType(STRING), mString(string)
	{
	}

	DataElement::DataElement(float number): mType(FLOAT), mFloat(number)
	{
	}

	DataElement::DataElement(int number): mType(INTEGER), mInt(number)
	{
	}

	DataElement::DataElement(long int number): mType(LONG), mLong(number)
	{
	}

	DataElement::~DataElement(void)
	{
	}

	DataElement::DataElement(const DataElement& original)
	{
		mType = original.getType();
		switch(mType)
		{
		case STRING:
			original.pollString(mString);
			break;
		case FLOAT:
			original.pollFloat(mFloat);
			break;
		case INTEGER:
			original.pollInteger(mInt);
			break;
		case LONG:
			original.pollLong(mLong);
			break;
		}
	}

	DataElement& DataElement::operator=(const DataElement& rhs)
	{
		if(this != &rhs)
		{
			mType = rhs.getType();
			switch(mType)
			{
			case STRING:
				rhs.pollString(mString);
				break;
			case FLOAT:
				rhs.pollFloat(mFloat);
				break;
			case INTEGER:
				rhs.pollInteger(mInt);
				break;
			case LONG:
				rhs.pollLong(mLong);
				break;
			}
		}
		return *this;
	}

	bool DataElement::pollString(std::string& string) const
	{
		if(mType != STRING)
		{
			return false;
		}
		else
		{
			string = std::string(mString);
			return true;
		}
	}

	bool DataElement::pollFloat(float& number) const
	{
		if(mType != FLOAT)
		{
			return false;
		}
		else
		{
			number = mFloat;
			return true;
		}
	}

	bool DataElement::pollInteger(int& number) const
	{
		if(mType != INTEGER)
		{
			return false;
		}
		else
		{
			number = mInt;
			return true;
		}
	}
	
	bool DataElement::pollLong(long int& number) const
	{
		if(mType != INTEGER && mType != LONG)
		{
			return false;
		}
		else
		{
			number = mLong;
			return true;
		}
	}

	bool DataElement::pollString(std::string& string, const std::string& defval) const
	{
		if(!pollString(string))
		{
			string = std::string(defval);
			return false;
		}
		return true;
	}

	bool DataElement::pollFloat(float& number, float defval) const
	{
		if(!pollFloat(number))
		{
			number = defval;
			return false;
		}
		return true;
	}

	bool DataElement::pollInteger(int& number, int defval) const
	{
		if(!pollInteger(number))
		{
			number = defval;
			return false;
		}
		return true;
	}

	bool DataElement::pollLong(long int& number, long int defval) const
	{
		if(!pollLong(number))
		{
			number = defval;
			return false;
		}
		return true;
	}
}	