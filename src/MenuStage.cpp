#include "MenuStage.h"

#include "Game.h"
#include "Board.h"
#include "Piece.h"

namespace sm
{
	const sf::Time MenuStage::TickingTimes[5] = {
		                                         sf::seconds(1),
			                                     sf::seconds(0.75),
			                                     sf::seconds(0.65),
			                                     sf::seconds(0.5),
			                                     sf::seconds(0.4)
	                                            };

	MenuStage::MenuStage(void): mClock(), mTime(), mTimeScale(0), 
		mBoard(), mPreviewBoard(), mCurrentPiece(), mNextPiece()
	{
		mTime = TickingTimes[mTimeScale];
	}

	void MenuStage::init(void)
	{
		mClock = Game::instance()->getMath()->createTimer();

		Game::instance()->getLogger()->getBuffer() << "MenuStage::init(void) called";
		Game::instance()->getLogger()->debug(5);

		mBoard = boost::shared_ptr<Board>(new Board(21, 11));
		mBoard->setPosition(20.f, 25.f);
		addEntity(boost::shared_ptr<Entity>(mBoard));

		mPreviewBoard = boost::shared_ptr<Board>(new Board(5, 5));
		mPreviewBoard->setPosition(225.f, 25.f);
		addEntity(boost::shared_ptr<Entity>(mPreviewBoard));

		mCurrentPiece = boost::shared_ptr<Piece>(new Piece(mBoard, 0, 5));

		mNextPiece = boost::shared_ptr<Piece>(new Piece(mPreviewBoard, 2, 2));
	}

	void MenuStage::update(void)
	{
		if(Game::instance()->getMath()->getTimeOfTimer(mClock) > mTime)
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("tick")));
			
			mTime = TickingTimes[mTimeScale] 
				- (Game::instance()->getMath()->getTimeOfTimer(mClock) - mTime);
			
			Game::instance()->getMath()->restartTimer(mClock);
		}

		if(mCurrentPiece)
		{
			mCurrentPiece->update();
		}

		State::update();
	}
}