#include "State.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace sm
{
	State::State(const std::string& id): mId(id), mBleep(false), mEntity(new Entity())
	{
	}

	State::State(const std::string& id, const bool bleep)
		: mId(id), mBleep(bleep), mEntity(new Entity())
	{
	}

	void State::addEntity(const boost::shared_ptr<Entity>& entity)
	{
		mEntity->addChild(boost::shared_ptr<Entity>(entity));
	}
	void State::clearEntities(void)
	{
		mEntity->clearChildren();
	}

	void State::update(void)
	{
		mEntity->update();
	}

	void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*mEntity.get(), states);
	}
}