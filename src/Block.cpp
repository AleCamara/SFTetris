#include "Block.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include "Game.h"
#include "MathSystem.h"

namespace sm
{
	const float Block::SIZE = 15.f;
	const float Block::PADDING = 2.f;

	const sf::Color Block::sColorArray[BlockColorCount] = {sf::Color::Blue,
		                                                   sf::Color::Magenta,
											               sf::Color::Green,
											               sf::Color::Yellow,
	   													   sf::Color::Red,
											               sf::Color(0x40, 0x40, 0x40, 255)};
	
	Block::Block(void): mActive(false), mMarked(false), mRectangle(sf::Vector2f(SIZE, SIZE))
	{
		deactivate();
	}

	Block::~Block(void)	{}

	void Block::activate(const BlockColor& color)
	{
		mActive = true;
		setColor(color);
		updateColor();
	}

	void Block::deactivate(void)
	{
		mActive = false;
		setColor(Grey);
		updateColor();
	}

	void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		target.draw(mRectangle, states);
		Entity::draw(target, states);
	}

	void Block::copyFrom(const Block& block)
	{
		if(block.isActive())
		{
			activate(block.getColor());
		}
		else
		{
			deactivate();
		}
		setMarkedForDeletion(block.isMarkedForDeletion());
	}

	Block::BlockColor Block::getRandomColor(void)
	{
		return convertIntToColor(Game::instance()->getMath()->getRandomInteger()
			% (BlockColorCount-1));
	}

	Block::BlockColor Block::convertIntToColor(int colorInt)
	{
		BlockColor out = Blue;

		switch(colorInt)
		{
		case 1:
			out = Magenta;
			break;
		case 2:
			out = Green;
			break;
		case 3:
			out = Yellow;
			break;
		case 4:
			out = Red;
			break;
		}

		return out;
	}

	void Block::updateColor(void)
	{
		mRectangle.setFillColor(sColorArray[mColor]);
	}
}