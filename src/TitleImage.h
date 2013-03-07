#pragma once

#include "Entity.h"
#include <vector>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

namespace sm
{
	class TitleImage: public Entity
	{
	public:
		TitleImage(void);
		virtual ~TitleImage(void);

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		typedef std::vector<sf::Text> TextContainer;

		sf::Texture mTexture;
		sf::Sprite mSprite;
		sf::Font mFont;
		TextContainer mTexts;
	};
}