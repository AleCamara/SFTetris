#include "Piece.h"

#include "Game.h"
#include "Board.h"

namespace sm
{

	Piece::Piece(const boost::shared_ptr<Board>& board, unsigned int row, unsigned int column)
		: mType(Bar), mColumn(column), mRow(row), mBoard(board), mStuck(false)
	{
		mType = getRandomType();
		mRotation = getRandomRotation();
		setNumBlocks();
		for(int k=0; k<mNumBlocks; ++k)
		{
			mColors[k] = Block::getRandomColor();
		}
		turnOn();
	}
	
	void Piece::update(void)
	{
		Game::ActionContainer::const_iterator iter = Game::instance()->getActions().cbegin();
		for(; iter != Game::instance()->getActions().cend(); ++iter)
		{
			if((*iter)->getString() == "tick")
			{
				updatePrivate();
				Game::instance()->getLogger()->getBuffer() << "Piece is " << mType << " and knows it has to update.";
				Game::instance()->getLogger()->debug(5);
				break;
			}
		}

		// move with player input
		if(!mStuck)
		{
			if(Game::instance()->getInput()->isKeyPressed(InputSystem::Key::Right))
			{
				movePrivate(MoveRight);
			}
			if(Game::instance()->getInput()->isKeyPressed(InputSystem::Key::Left))
			{
				movePrivate(MoveLeft);
			}
			if(Game::instance()->getInput()->isKeyPressed(InputSystem::Key::Down))
			{
				movePrivate(MoveDown);
			}
			if(Game::instance()->getInput()->isKeyReleased(InputSystem::Key::A))
			{
				rotatePrivate(CCW);
			}
			if(Game::instance()->getInput()->isKeyReleased(InputSystem::Key::S))
			{
				rotatePrivate(CW);
			}
		}
	}

	void Piece::updatePrivate(void)
	{
		if(movePrivate(MoveDown))
		{
			Game::instance()->getLogger()->getBuffer() << "Piece is stuck!";
			Game::instance()->getLogger()->debug(5);
			mStuck = true;
			return;
		}
	}

	bool Piece::movePrivate(Direction dir)
	{
		bool out = hitOnMove(dir);

		if(!out)
		{
			turnOff();

			int dRow, dColumn;
			getMovementVariations(dir, dRow, dColumn);
			setRow(getRow() + dRow);
			setColumn(getColumn() + dColumn);

			turnOn();
		}

		return out;
	}

	bool Piece::rotatePrivate(Rotation rot)
	{
		bool out = hitOnRotate(rot);

		if(!out)
		{
			int dRot;
			getRotationVariation(rot, dRot);

			turnOff();
			mRotation = (mRotation + dRot) % RotationCount;
			turnOn();
		}

		return out;
	}

	bool Piece::hitOnMove(Direction dir) const
	{
		bool out = false;

		// displacement
		int dRow = 0, dColumn = 0;
		getMovementVariations(dir, dRow, dColumn);

		// deactivate current piece
		turnOff();

		// check hit
		int row = 0, column = 0;
		for(int k=0; k<mNumBlocks; ++k)
		{
			row = mRow + BlockRow[mType][mRotation][k] + dRow;
			column = mColumn + BlockColumn[mType][mRotation][k] + dColumn;

			// hit a wall
			if((dir == MoveUp && row < 0) || 
			   (dir == MoveDown && row >= mBoard->getNumRows()) || 
			   (dir == MoveLeft && column < 0) ||
			   (dir == MoveRight && column >= mBoard->getNumColumns()))
			{
				out = true;
				break;
			}

			// hit another piece
			// note that row and column are valid board indices
			if(mBoard->checkBoardPosition(row, column))
			{
				out = true;
				break;
			}
		}

		// activate blocks
		turnOn();

		return out;
	}

	bool Piece::hitOnRotate(Rotation rot) const
	{
		bool out = false;

		// displacement
		int dRot = 0;
		getRotationVariation(rot, dRot);
		unsigned int newRot = (mRotation + dRot) % RotationCount;

		// deactivate current piece
		turnOff();

		// check hit
		int row = 0, column = 0;
		for(int k=0; k<mNumBlocks; ++k)
		{
			row = mRow + BlockRow[mType][newRot][k];
			column = mColumn + BlockColumn[mType][newRot][k];

			// hit a wall
			if(row < 0 || row >= mBoard->getNumRows() || 
			   column < 0 || column >= mBoard->getNumColumns())
			{
				out = true;
				break;
			}

			// hit another piece
			// note that row and column are valid board indices
			if(mBoard->checkBoardPosition(row, column))
			{
				out = true;
				break;
			}
		}

		// activate blocks
		turnOn();

		return out;
	}

	void Piece::turnOn(void) const
	{
		int row = 0, column = 0;
		for(int k=0; k<mNumBlocks; ++k)
		{
			row = mRow + BlockRow[mType][mRotation][k];
			column = mColumn + BlockColumn[mType][mRotation][k];
			mBoard->changeBlockColor(row, column, mColors[k]);
			mBoard->activateBlock(row, column);
		}
	}

	void Piece::turnOff(void) const
	{
		int row = 0, column = 0;
		for(int k=0; k<mNumBlocks; ++k)
		{
			row = mRow + BlockRow[mType][mRotation][k];
			column = mColumn + BlockColumn[mType][mRotation][k];
			mBoard->deactivateBlock(row, column);
		}
	}

	void Piece::setNumBlocks(void)
	{
		if(mType == SnakeR || mType == SnakeL)
		{
			mNumBlocks = 5;
		}
		else
		{
			mNumBlocks = 4;
		}
	}

	void Piece::getMovementVariations(Direction dir, int& dRow, int& dColumn) const
	{
		dRow = 0;
		dColumn = 0;
		switch(dir)
		{
		case MoveDown:
			dRow = +1;
			break;
		case MoveUp:
			dRow = -1;
			break;
		case MoveLeft:
			dColumn = -1;
			break;
		case MoveRight:
			dColumn = +1;
			break;
		}
	}

	void Piece::getRotationVariation(Rotation rot, int& dRot) const
	{
		dRot = +1;
		if(rot == CCW)
		{
			dRot = -1;
		}
	}

	Piece::Type Piece::getRandomType(void) const
	{
		return convertIntToType(Game::instance()->getMath()->getRandomInteger() % PieceCount);
	}

	Piece::Type Piece::convertIntToType(int typeInt) const
	{
		Type type = Bar;

		switch(typeInt)
		{
		case 1:
			type = Square;
			break;
		case 2:
			type = SnakeR;
			break;
		case 3:
			type = SnakeL;
			break;
		case 4:
			type = NailR;
			break;
		case 5:
			type = NailL;
			break;
		case 6:
			type = T;
			break;
		}

		return type;
	}

	unsigned int Piece::getRandomRotation(void) const
	{
		return Game::instance()->getMath()->getRandomInteger() % RotationCount;
	}

	const int Piece::BlockColumn[PieceCount][RotationCount][5]
			= {
				// Bar
				{
				  { 0,  0,  0,  0, 0},
				  { 1,  0, -1, -2, 0},
				  { 0,  0,  0,  0, 0},
				  {-1,  0,  1,  2, 0}
				},
				// Square
				{
				  { 0,  1,  1,  0, 0},
				  { 0,  0, -1, -1, 0},
				  { 0, -1, -1,  0, 0},
				  { 0,  0,  1,  1, 0}
				},
				// SnakeR
				{
				  { 1,  0, 0,  0, -1},
				  { 1,  1, 0, -1, -1},
				  {-1,  0, 0,  0,  1},
				  {-1, -1, 0,  1,  1}
				},
				// SnakeL
				{
				  {-1,  0, 0,  0,  1},
				  { 1,  1, 0, -1, -1},
				  { 1,  0, 0,  0, -1},
				  {-1, -1, 0,  1,  1}
				},
				// NailR
				{
				  { 1,  0,  0,  0, 0},
				  { 1,  1,  0, -1, 0},
				  {-1,  0,  0,  0, 0},
				  {-1, -1,  0,  1, 0}
				},
				// NailL
				{
				  {-1,  0, 0,  0, 0},
				  { 1,  1, 0, -1, 0},
				  { 1,  0, 0,  0, 0},
				  {-1, -1, 0,  1, 0}
				},
				// T
				{
				  {-1,  0,  1,  0, 0},
				  { 0,  0,  0, -1, 0},
				  { 1,  0, -1,  0, 0},
				  { 0,  0,  0,  1, 0}
				}
			  };
	const int Piece::BlockRow[PieceCount][RotationCount][5]
			= {
				// Bar
				{
				  {-1,  0,  1,  2, 0},
				  { 0,  0,  0,  0, 0},
				  { 1,  0, -1, -2, 0},
				  { 0,  0,  0,  0, 0}
				},
				// Square
				{
				  { 0,  0,  1,  1, 0},
				  { 0,  1,  1,  0, 0},
				  { 0,  0, -1, -1, 0},
				  { 0, -1, -1,  0, 0}
				},
				// SnakeR
				{
				  {-1, -1, 0,  1,  1},
				  { 1,  0, 0,  0, -1},
				  { 1,  1, 0, -1, -1},
				  {-1,  0, 0,  0,  1}
				},
				// SnakeL
				{
				  {-1, -1, 0,  1,  1},
				  {-1,  0, 0,  0,  1},
				  { 1,  1, 0, -1, -1},
				  { 1,  0, 0,  0, -1}
				},
				// NailR
				{
				  {-1, -1, 0,  1, 0},
				  { 1,  0, 0,  0, 0},
				  { 1,  1, 0, -1, 0},
				  {-1,  0, 0,  0, 0}
				},
				// NailL
				{
				  {-1, -1, 0,  1, 0},
				  {-1,  0, 0,  0, 0},
				  { 1,  1, 0, -1, 0},
				  { 1,  0, 0,  0, 0}
				},
				// T
				{
				  { 0, 0,  0,  1, 0},
				  {-1, 0,  1,  0, 0},
				  { 0, 0,  0, -1, 0},
				  { 1, 0, -1,  0, 0}
				}
			  };
}