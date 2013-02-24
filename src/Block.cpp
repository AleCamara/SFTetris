#include "Block.h"

#include <stdlib.h>
#include <time.h>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

namespace sm
{
	const sf::Color Block::sColorArray[Block::BlockColor::Count] = {sf::Color::Blue,
		                                                            sf::Color::Magenta,
											                        sf::Color::Green,
											                        sf::Color::Yellow,
											                        sf::Color::Red};

	Block::Block(void)
	{
		mColor = getRandomColor();
		setPosition(rand() % 300, rand() % 400);
	}

	Block::~Block(void)	{}

	void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		sf::RectangleShape rect(sf::Vector2f(15, 15));
		rect.setFillColor(sColorArray[mColor]);
		target.draw(rect, states);
		Entity::draw(target, states);
	}

	Block::BlockColor Block::getRandomColor(void)
	{
		BlockColor out = Blue;

		switch(int(rand() % Block::BlockColor::Count))
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