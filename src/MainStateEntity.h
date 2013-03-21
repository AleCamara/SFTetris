#pragma once

#include "Entity.h"

#include <vector>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

namespace sm
{
	class MainState;

	class MainStateEntity: public Entity
	{
	public:
		MainStateEntity(void);
		virtual ~MainStateEntity(void);

		virtual void update(void);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		typedef std::vector<sf::Text> TextContainer;
		
		boost::shared_ptr<MainState> mMainState;
		sf::Font mFont;
		TextContainer mTexts;

		void updateLabels(void);
	};
}