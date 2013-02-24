#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Color.hpp>
#include "Entity.h"

namespace sm
{
	class Block: public Entity
	{
	public:
		static const float SIZE;
		static const float PADDING;

		Block(void);
		virtual ~Block(void);

		void activate(void);
		void deactivate(void);
		bool checkActive(void) const { return mActive; }

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		enum BlockColor {
			GREY = -1,
			Blue = 0,
			Magenta,
			Green,
			Yellow,
			Red,
			Count,
			CountAll
		};
		
		static const sf::Color sColorArray[BlockColor::CountAll];

		BlockColor mColor;
		bool mActive;
		sf::RectangleShape mRectangle;

		BlockColor getRandomColor(void);
	};
}