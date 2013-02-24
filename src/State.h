#pragma once

#include <boost\scoped_ptr.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include "Mutable.h"
#include "Entity.h"

namespace sm
{
	class State: public IMutable, public sf::Drawable
	{
	public:
		typedef unsigned int IdType;

		State(void);
		virtual ~State(void);

		IdType getId(void) const { return mId; }

		void addEntity(Entity *);
		void clearEntities(void);

		virtual void init(void) {}

		virtual void update(void);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		static IdType sCurrentId;
		IdType mId;
		boost::scoped_ptr<Entity> mEntity;
	};
}