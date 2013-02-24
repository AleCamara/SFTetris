#include "Entity.h"

#include <SFML\Graphics\RenderTarget.hpp>

namespace sm
{
	Entity::Entity(void): mChildren() {}
	Entity::~Entity(void) {}

	void Entity::addChild(Entity *child)
	{
		mChildren.push_back(boost::shared_ptr<Entity>(child));
	}
	void Entity::clearChildren(void)
	{
		mChildren.clear();
	}

	void Entity::update(void)
	{
		ChildrenContainerType::iterator iter = mChildren.begin();
		for(; iter != mChildren.end(); iter++)
		{
			(*iter)->update();
		}
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		ChildrenContainerType::const_iterator iter = mChildren.cbegin();
		for(; iter != mChildren.cend(); iter++)
		{
			target.draw(*(iter->get()), states);
		}
	}
}