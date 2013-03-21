#include "DataList.h"

#include "DataElement.h"

namespace sm
{
	DataList::DataList(void): mData()
	{
	}

	DataList::~DataList(void)
	{
	}

	void DataList::insertData(const std::string& key, const boost::shared_ptr<DataElement>& data)
	{
		mData.insert(DataContainer::value_type(key, boost::shared_ptr<DataElement>(data)));
	}

	void DataList::removeData(const std::string& key)
	{
		mData.erase(key);
	}

	void DataList::clear(void)
	{
		mData.clear();
	}

	bool DataList::pollString(const std::string& key, std::string& value) const
	{
		return pollString(key, value, std::string());
	}

	bool DataList::pollFloat(const std::string& key, float& value) const
	{
		return pollFloat(key, value, 0.f);
	}

	bool DataList::pollInteger(const std::string& key, int& value) const
	{
		return pollInteger(key, value, 0);
	}

	bool DataList::pollLong(const std::string& key, long int& value) const
	{
		return pollLong(key, value, 0L);
	}

	bool DataList::pollString(const std::string& key, std::string& value,
		const std::string& defval) const
	{
		DataContainer::const_iterator match = mData.find(key);
		if(match != mData.cend())
		{
			return ((*match).second)->pollString(value, defval);
		}
		return false;
	}

	bool DataList::pollFloat(const std::string& key, float& value,
		float defval) const
	{
		DataContainer::const_iterator match = mData.find(key);
		if(match != mData.cend())
		{
			return ((*match).second)->pollFloat(value, defval);
		}
		return false;
	}

	bool DataList::pollInteger(const std::string& key, int& value,
		int defval) const
	{
		DataContainer::const_iterator match = mData.find(key);
		if(match != mData.cend())
		{
			return ((*match).second)->pollInteger(value, defval);
		}
		return false;
	}

	bool DataList::pollLong(const std::string& key, long int& value,
		long int defval) const
	{
		DataContainer::const_iterator match = mData.find(key);
		if(match != mData.cend())
		{
			return ((*match).second)->pollLong(value, defval);
		}
		return false;
	}

}