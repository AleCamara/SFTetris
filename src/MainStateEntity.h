#pragma once

#include "Entity.h"

#include <vector>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

namespace sm
{
	class MainStateEntity: public Entity
	{
	public:
		MainStateEntity(void);
		virtual ~MainStateEntity(void);

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		typedef std::vector<sf::Text> TextContainer;

		sf::Font mFont;
		TextContainer mTexts;
	};
}