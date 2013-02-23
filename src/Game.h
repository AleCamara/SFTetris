#pragma once

#include <string>
#include <boost\scoped_ptr.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "State.h"
#include "Logger.h"

namespace sm
{
	class Game : public sf::RenderWindow
	{
	public:
		static Game *instance();

		~Game(void);

		void setStage(State*);

		Logger *getLogger(void);

		void loop(void);

	private:
		static Game *sInstance;

		static const unsigned int FRAMERATE;
		static const sf::VideoMode VIDEO_MODE;
		static const std::string TITLE;
		static const unsigned int STYLE;

		boost::scoped_ptr<State> mStage;
		boost::scoped_ptr<Logger> mLogger;

		Game(void);
		Game(const Game&) {}
		Game& operator=(const Game&) {}
	};
}