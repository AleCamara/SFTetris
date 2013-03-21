#include "MainStateEntity.h"

#include <iomanip>
#include <sstream>
#include <SFML\Graphics\RenderTarget.hpp>
#include "MainState.h"
#include "Game.h"
#include "Action.h"
#include "DataList.h"

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
		// calculate points
		const Game::ActionContainer actions = Game::instance()->getActions();
		Game::ActionContainer::const_iterator action = actions.cbegin();
		for(; action != actions.cend(); ++action)
		{
			if((*action)->getId() == "score_changed")
			{
				long int score = 0;
				if((*action)->getData()->pollLong("score", score))
				{
					std::stringstream ss;
					ss << std::setw(7) << std::setfill('0') << score;
					mTexts[1].setString(ss.str());
				}
			}

			if((*action)->getId() == "level_changed")
			{
				int level = 0;
				if((*action)->getData()->pollInteger("level", level))
				{
					std::stringstream ss;
					ss << level;
					mTexts[3].setString(ss.str());
				}
			}
		}
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