#pragma once

#include <string>

namespace sm
{
	class DataElement
	{
	public:
		enum Type
		{
			STRING,
			FLOAT,
			INTEGER,
			LONG
		};

		DataElement(const std::string&);
		DataElement(float);
		DataElement(int);
		DataElement(long int);
		~DataElement(void);

		// copy constructible and asignable by operator=
		DataElement(const DataElement&);
		DataElement& operator=(const DataElement&);

		Type getType(void) const { return mType; }

		// no default value
		bool pollString(std::string&) const;
		bool pollFloat(float&) const;
		bool pollInteger(int&) const;
		bool pollLong(long int&) const;

		// default value
		bool pollString(std::string&, const std::string&) const;
		bool pollFloat(float&, float) const;
		bool pollInteger(int&, int) const;
		bool pollLong(long int&, long int) const;

	private:
		Type mType;
		std::string mString;
		float mFloat;
		int mInt;
		long int mLong;
	};
}