#include "MainStateEntity.h"

#include <SFML\Graphics\RenderTarget.hpp>

namespace sm
{
	MainStateEntity::MainStateEntity(void): Entity(), mFont(), mTexts()
	{
		mFont.loadFromFile("assets/pixel.ttf");

		mTexts.push_back(sf::Text("Next", mFont, 24U));

		mTexts[0].setPosition(227.f, 260.f);

		mTexts[0].setColor(sf::Color(255U, 77U, 61U, 255U));
	}


	MainStateEntity::~MainStateEntity(void)
	{
	}

	void MainStateEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		TextContainer::const_iterator text = mTexts.cbegin();
		for(; text != mTexts.cend(); ++text)
		{
			target.draw(*text, states);
		}
	}
}