#pragma once

#include <boost\shared_ptr.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include "Mutable.h"
#include "Entity.h"

namespace sm
{
	class State: public IMutable, public sf::Drawable
	{
	public:

		State(const std::string&);
		State(const std::string&, const bool);
		virtual ~State(void) {}

		std::string getId(void) const { return mId; }
		bool isBleep(void) const { return mBleep; }

		void addEntity(const boost::shared_ptr<Entity>&);
		void clearEntities(void);

		virtual void init(void) {}
		virtual void update(void);
		virtual void quit(void) {}
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		const std::string mId;
		const bool mBleep;
		boost::shared_ptr<Entity> mEntity;
	};
}