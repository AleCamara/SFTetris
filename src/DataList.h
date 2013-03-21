#pragma once

#include <string>
#include <hash_map>
#include <boost\shared_ptr.hpp>

namespace sm
{
	class DataElement;

	class DataList
	{
	public:
		DataList(void);
		~DataList(void);

		void insertData(const std::string&, const boost::shared_ptr<DataElement>&);
		void removeData(const std::string&);
		void clear(void);

		// no default value
		bool pollString(const std::string&, std::string&) const;
		bool pollFloat(const std::string&, float&) const;
		bool pollInteger(const std::string&, int&) const;
		bool pollLong(const std::string&, long int&) const;

		// default value
		bool pollString(const std::string&, std::string&, const std::string&) const;
		bool pollFloat(const std::string&, float&, float) const;
		bool pollInteger(const std::string&, int&, int) const;
		bool pollLong(const std::string&, long int&, long int) const;

	private:
		typedef std::hash_map<std::string,boost::shared_ptr<DataElement>> DataContainer;

		DataContainer mData;
	};
}