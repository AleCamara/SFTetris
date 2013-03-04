#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Color.hpp>
#include "Entity.h"

namespace sm
{
	class Block: public Entity
	{
	public:
		enum BlockColor
		{
			Blue = 0,
			Magenta,
			Green,
			Yellow,
			Red,
			Grey,
			BlockColorCount
		};

		static const float SIZE;
		static const float PADDING;
		
		static BlockColor getRandomColor(void);

		Block(void);
		virtual ~Block(void);

		void activate(void);
		void deactivate(void);
		bool checkActive(void) const { return mActive; }
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

		void setColor(BlockColor color) { mColor = color; }
		BlockColor getColor(void) const { return mColor; }
		
	private:
		static const sf::Color sColorArray[BlockColorCount];
		
		static BlockColor convertIntToColor(int);

		BlockColor mColor;
		bool mActive;
		sf::RectangleShape mRectangle;

		
	};
}