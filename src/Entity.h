#pragma once

#include <list>
#include <boost\shared_ptr.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include "Mutable.h"

namespace sm
{
	class Entity: public IMutable, public sf::Drawable, public sf::Transformable
	{
	public:
		Entity(void);
		virtual ~Entity(void);

		void addChild(Entity *);
		void clearChildren(void);

		/* IMutable and Drawable interfaces */
		virtual void update(void);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		typedef std::list<boost::shared_ptr<Entity>> ChildrenContainerType;
		std::list<boost::shared_ptr<Entity>> mChildren;
	};
}