#include "GameOverEntity.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace sm
{
	GameOverEntity::GameOverEntity(void): Entity(), mTexture(), mSprite(), mFont(), mTexts()
	{
		mTexture.loadFromFile("assets/menu.png");
		mSprite.setTexture(mTexture);
		mSprite.setPosition(0.f, 0.f);
		
		mFont.loadFromFile("assets/pixel.ttf");

		mTexts.push_back(sf::Text("Game Over", mFont, 32U));
		mTexts.push_back(sf::Text("[A]", mFont, 24U));
		mTexts.push_back(sf::Text("[ESC]", mFont, 24U));
		mTexts.push_back(sf::Text("Restart", mFont, 24U));
		mTexts.push_back(sf::Text("Title", mFont, 24U));

		mTexts[0].setPosition(85.f,  125.f);
		mTexts[1].setPosition(110.f, 180.f);
		mTexts[2].setPosition(86.f,  220.f);
		mTexts[3].setPosition(150.f, 180.f);
		mTexts[4].setPosition(150.f, 220.f);
		
		mTexts[0].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[1].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[2].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[3].setColor(sf::Color(255U, 216U, 0U, 255U));
		mTexts[4].setColor(sf::Color(255U, 216U, 0U, 255U));
	}

	GameOverEntity::~GameOverEntity(void)
	{
	}

	void GameOverEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
		TextContainer::const_iterator text = mTexts.cbegin();
		for(; text != mTexts.cend(); ++text)
		{
			target.draw(*text, states);
		}
	}
}