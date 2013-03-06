#pragma once

#include <SFML\System\Time.hpp>
#include "State.h"

namespace sm
{
	class Board;
	class Piece;

	class MenuStage: public State
	{
	public:
		MenuStage(void);
		virtual ~MenuStage(void) {}

		virtual void init(void);
		virtual void update(void);
		virtual void quit(void);

	private:
		static const sf::Time TickingTimes[5];

		unsigned int mClock;
		sf::Time mTime;
		unsigned int mTimeScale;
		unsigned int mMusicPiece;
		
		boost::shared_ptr<Board> mBoard;
		boost::shared_ptr<Board> mPreviewBoard;
		boost::shared_ptr<Piece> mCurrentPiece;
		boost::shared_ptr<Piece> mNextPiece;

	};
}