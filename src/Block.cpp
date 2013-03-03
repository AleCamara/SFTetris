#include "Block.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include "Game.h"

namespace sm
{
	const float Block::SIZE = 15.f;
	const float Block::PADDING = 2.f;

	const sf::Color Block::sColorArray[Block::BlockColor::Count] = {sf::Color::Blue,
		                                                            sf::Color::Magenta,
											                        sf::Color::Green,
											                        sf::Color::Yellow,
	   														   	    sf::Color::Red,
											                        sf::Color(0x40, 0x40, 0x40, 255)};
	
	Block::Block(void): mActive(false), mRectangle(sf::Vector2f(SIZE, SIZE))
	{
		mColor = getRandomColor();
		deactivate();
	}

	Block::~Block(void)	{}

	void Block::activate(void)
	{
		mActive = true;
		mRectangle.setFillColor(sColorArray[mColor]);
	}

	void Block::deactivate(void)
	{
		mActive = false;
		mRectangle.setFillColor(sColorArray[Grey]);
	}

	void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		target.draw(mRectangle, states);
		Entity::draw(target, states);
	}

	Block::BlockColor Block::getRandomColor(void) const
	{
		return convertIntToColor(Game::instance()->getMath()->getRandomInteger()
			% (Block::BlockColor::Count-1));
	}

	Block::BlockColor Block::convertIntToColor(int colorInt) const
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
}