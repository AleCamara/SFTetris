#pragma once

#include <string>
#include <boost\shared_ptr.hpp>

namespace sm
{
	class DataList;
	class DataElement;

	class Action
	{
	public:
		Action(const std::string&);
		~Action(void) {}

		const std::string& getId(void) const { return mId; }

		boost::shared_ptr<DataList> getData(void) const { return mData; }
		void insertData(const std::string&, const DataElement&);

	private:
		std::string mId;
		boost::shared_ptr<DataList> mData;
	};
}