#include "MainState.h"

#include "Game.h"
#include "Board.h"
#include "Piece.h"
#include "Action.h"
#include "Logger.h"
#include "MathSystem.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "MainStateEntity.h"
#include "DataList.h"
#include "DataElement.h"

namespace sm
{
	const sf::Time MainState::TickingTimes[5] = {
		                                         sf::seconds(0.9f),
			                                     sf::seconds(0.6f),
			                                     sf::seconds(0.4f),
			                                     sf::seconds(0.3f),
			                                     sf::seconds(0.2f)
	                                            };

	const float MainState::Scores[5] = { 10.f, 10.f*2.f, 10.f*4.f, 10.f*8.f, 10.f*16.f };

	const float MainState::NextLevel[4] = { 250.f, 2000.f, 16000.f, 32000.f};

	MainState::MainState(void): State("game"), mClock(), mTime(), mTimeScale(0), 
		mMusicPiece(), mScore(0L), mBoard(), mPreviewBoard(), mCurrentPiece(), mNextPiece()		
	{
		mTime = TickingTimes[mTimeScale];
	}

	void MainState::init(void)
	{
		init(Action("empty"));
	}

	void MainState::init(const Action& action)
	{
		mClock = Game::instance()->getMath()->createTimer();

		Game::instance()->getLogger()->getBuffer() << "MainState::init()";
		Game::instance()->getLogger()->debug(5);

		mBoard = boost::shared_ptr<Board>(new Board(21, 11));
		mBoard->setPosition(20.f, 25.f);
		addEntity(boost::shared_ptr<Entity>(mBoard));

		mPreviewBoard = boost::shared_ptr<Board>(new Board(5, 5));
		mPreviewBoard->setPosition(225.f, 297.f);
		addEntity(boost::shared_ptr<Entity>(mPreviewBoard));

		mCurrentPiece = boost::shared_ptr<Piece>(new Piece(mBoard, 0, 5));
		mNextPiece = boost::shared_ptr<Piece>(new Piece(mPreviewBoard, 2, 2));

		mMusicPiece = Game::instance()->getAudio()->createMusicPiece();
		Game::instance()->getAudio()->getMusicPiece(mMusicPiece)->openFromFile("assets/main_theme.ogg");
		Game::instance()->getAudio()->getMusicPiece(mMusicPiece)->setLoop(true);
		Game::instance()->getAudio()->playMusicPiece(mMusicPiece);

		addEntity(boost::shared_ptr<Entity>(new MainStateEntity()));
	}

	void MainState::update(void)
	{
		// calculate points
		const Game::ActionContainer actions = Game::instance()->getActions();
		Game::ActionContainer::const_iterator action = actions.cbegin();
		for(; action != actions.cend(); ++action)
		{
			if((*action)->getId() == "delete_block_result")
			{
				int deleted = 0;
				if((*action)->getData()->pollInteger("result", deleted) && deleted > 0)
				{
					long int score_inc = (long int) (deleted*Scores[mTimeScale]);
					mScore += score_inc;
					boost::shared_ptr<Action> action(new Action("score_changed"));
					action->insertData("score", DataElement(mScore));
					Game::instance()->addAction(action);

					if(mScore > NextLevel[mTimeScale])
					{
						++mTimeScale;
						boost::shared_ptr<Action> action(new Action("level_changed"));
						action->insertData("level", DataElement((int)mTimeScale));
						Game::instance()->addAction(action);
					}
				}
			}
		}

		if(Game::instance()->getMath()->getTimeOfTimer(mClock) > mTime)
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("tick")));
			
			mTime = TickingTimes[mTimeScale] 
				- (Game::instance()->getMath()->getTimeOfTimer(mClock) - mTime);
			
			Game::instance()->getMath()->restartTimer(mClock);
		}

		if(!mCurrentPiece->isStuck())
		{
			mCurrentPiece->update();
		}
		else
		{
			// prepare preview piece to be a current piece
			mCurrentPiece = mNextPiece;
			mCurrentPiece->setBoard(mBoard);
			mCurrentPiece->setRow(0);
			mCurrentPiece->setColumn(5);
			
			// create a new preview piece
			mPreviewBoard->resetBlocks();
			mNextPiece.reset(new Piece(mPreviewBoard, 2, 2));

			// check for game over
			if(mCurrentPiece->checkCollision())
			{
				Game::instance()->getLogger()->getBuffer() << "GAME OVER!";
				Game::instance()->getLogger()->debug(5);
			}
			// check for block deletion
			else
			{
				mCurrentPiece->turnOff();
				mBoard->checkHorizontal();
				mBoard->checkColors();
				mBoard->deleteMarkedBlocks();
				mCurrentPiece->turnOn();
			}
		}

		if(Game::instance()->getInput()->isKeyReleased(InputSystem::Keyboard::Escape))
		{
			Game::instance()->addAction(boost::shared_ptr<Action>(new Action("gomenu")));
		}

		State::update();
	}

	void MainState::quit(void)
	{
		Game::instance()->getLogger()->getBuffer() << "MainState::quit()";
		Game::instance()->getLogger()->debug(5);
		Game::instance()->getAudio()->stopMusic();
	}
}	