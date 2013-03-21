#include "MainStateEntity.h"

#include <iomanip>
#include <sstream>
#include <SFML\Graphics\RenderTarget.hpp>
#include "MainState.h"

namespace sm
{
	MainStateEntity::MainStateEntity(void)
		: Entity(), mFont(), mTexts()
	{
		mFont.loadFromFile("assets/pixel.ttf");

		mTexts.push_back(sf::Text("Score", mFont, 24U));
		mTexts.push_back(sf::Text("0000000", mFont, 16U));
		mTexts.push_back(sf::Text("Level", mFont, 24U));
		mTexts.push_back(sf::Text("0", mFont, 16U));
		mTexts.push_back(sf::Text("Next", mFont, 24U));

		mTexts[0].setPosition(227.f, 26.f);
		mTexts[1].setPosition(252.f, 66.f);
		mTexts[2].setPosition(227.f, 141.f);
		mTexts[3].setPosition(252.f, 181.f);
		mTexts[4].setPosition(227.f, 260.f);
		
		mTexts[0].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[1].setColor(sf::Color(255U, 216U, 0U, 255U));
		mTexts[2].setColor(sf::Color(255U, 77U, 61U, 255U));
		mTexts[3].setColor(sf::Color(255U, 216U, 0U, 255U));
		mTexts[4].setColor(sf::Color(255U, 77U, 61U, 255U));
	}


	MainStateEntity::~MainStateEntity(void)
	{
	}

	void MainStateEntity::update(void)
	{
		std::stringstream ss;
		ss << std::setw(7) << std::setfill('0') << '0';
		mTexts[1].setString(ss.str());

		ss.str(std::string());
		ss << "0";
		mTexts[3].setString(ss.str());
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