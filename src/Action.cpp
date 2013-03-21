#include "Action.h"

#include "Game.h"
#include "DataList.h"
#include "DataElement.h"

namespace sm
{
	Action::Action(const std::string& id): mId(id), mData(new DataList())
	{
	}

	void Action::insertData(const std::string& key, const DataElement& data)
	{
		mData->insertData(key, boost::shared_ptr<DataElement>(new DataElement(data)));
	}
}