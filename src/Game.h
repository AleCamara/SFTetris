#pragma once

#include <string>
#include <vector>
#include <boost\shared_ptr.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML\System\Time.hpp>
#include "State.h"
#include "Logger.h"
#include "MathSystem.h"
#include "InputSystem.h"
#include "Action.h"

namespace sm
{
	class Game : public sf::RenderWindow
	{
	public:
		typedef std::vector<boost::shared_ptr<Action>> ActionContainer;

		static boost::shared_ptr<Game> instance();

		~Game(void);

		void setStage(boost::shared_ptr<State>);

		boost::shared_ptr<InputSystem> getInput(void);
		boost::shared_ptr<MathSystem> getMath(void);
		boost::shared_ptr<Logger> getLogger(void);

		void addAction(const boost::shared_ptr<Action>&);
		const ActionContainer& getActions(void) const;

		sf::Time getDeltaTime(void) const;

		void loop(void);

	private:
		static boost::shared_ptr<Game> sInstance;

		static const unsigned int FRAMERATE;
		static const sf::VideoMode VIDEO_MODE;
		static const std::string TITLE;
		static const unsigned int STYLE;

		boost::shared_ptr<State> mStage;
		boost::shared_ptr<Logger> mLogger;
		boost::shared_ptr<MathSystem> mMath;
		boost::shared_ptr<InputSystem> mInput;
		ActionContainer mActions;
		sf::Clock mDeltaClock;
		sf::Time mDeltaTime;

		Game(void);
		Game(const Game&) {}
		Game& operator=(const Game&) {}
	};
}