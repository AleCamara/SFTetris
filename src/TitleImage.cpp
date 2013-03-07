#include "TitleImage.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace sm
{
	TitleImage::TitleImage(void): mTexture(), mSprite(), mFont(), mTexts()
	{
		mTexture.loadFromFile("assets/title.png");
		mSprite.setTexture(mTexture);
		mSprite.setPosition(0.f, 0.f);

		mFont.loadFromFile("assets/pixel.ttf");

		mTexts.push_back(sf::Text("[A]", mFont, 24U));
		mTexts.push_back(sf::Text("[ESC]", mFont, 24U));
		mTexts.push_back(sf::Text("New Game", mFont, 24U));
		mTexts.push_back(sf::Text("Exit", mFont, 24U));
		mTexts.push_back(sf::Text("Sismicos (c) 2013", mFont, 16U));

		mTexts[0].setPosition(100.f, 210.f);
		mTexts[1].setPosition(76.f, 250.f);
		mTexts[2].setPosition(140.f, 210.f);
		mTexts[3].setPosition(140.f, 250.f);
		mTexts[4].setPosition(175.f, 375.f);

		mTexts[0].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[1].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[2].setColor(sf::Color(255U, 216U, 0U, 255U));
		mTexts[3].setColor(sf::Color(255U, 216U, 0U, 255U));
		mTexts[4].setColor(sf::Color(0U, 148U, 255U, 255U));
	}

	TitleImage::~TitleImage(void)
	{
	}

	void TitleImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
		TextContainer::const_iterator text = mTexts.cbegin();
		for(; text != mTexts.cend(); ++text)
		{
			target.draw(*text, states);
		}
	}
}