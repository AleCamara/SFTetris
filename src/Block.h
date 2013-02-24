#pragma once

#include <SFML\Graphics\Color.hpp>
#include "Entity.h"

namespace sm
{
	class Block: public Entity
	{
	public:
		Block(void);
		virtual ~Block(void);

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		enum BlockColor {
			Blue,
			Magenta,
			Green,
			Yellow,
			Red,
			Count
		};
		
		static const sf::Color sColorArray[BlockColor::Count];

		BlockColor mColor;

		BlockColor getRandomColor(void);
	};
}