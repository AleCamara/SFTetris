#include "State.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace sm
{
	State::IdType State::sCurrentId = 0;

	State::State(void): mId(0), mEntity(new Entity())
	{
		mId = sCurrentId++;
	}

	State::~State(void)	{}

	void State::addEntity(Entity *entity)
	{
		mEntity->addChild(entity);
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