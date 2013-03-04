#pragma once

#include <boost\shared_ptr.hpp>
#include "Entity.h"
#include "Block.h"

namespace sm
{
	class Board;

	class Piece: public Entity
	{
	public:
		enum Type
		{
			Bar = 0,
			Square,
			SnakeR,
			SnakeL,
			NailR,
			NailL,
			T,
			PieceCount
		};

		// create a random piece at given board position
		Piece(const boost::shared_ptr<Board>&, unsigned int, unsigned int);

		virtual ~Piece(void) {}

		void setBoard(const boost::shared_ptr<Board>&);

		void setRow(int row) { mRow = row; }
		int getRow(void) const { return mRow; }
		void setColumn(int column) { mColumn = column; }
		int getColumn(void) const { return mColumn; }

		bool isStuck(void) const { return mStuck; }

		virtual void update(void);

	private:
		enum Direction
		{
			MoveDown,
			MoveLeft,
			MoveRight,
			MoveUp
		};

		enum Rotation
		{
			CW,
			CCW
		};

		static const int sNumBlocks = 4;
		static const int sRotationCount = 4;
		static const int BlockRow[PieceCount][sRotationCount][sNumBlocks];
		static const int BlockColumn[PieceCount][sRotationCount][sNumBlocks];

		Type mType;
		unsigned int mRotation;
		int mColumn, mRow;
		boost::shared_ptr<Board> mBoard;
		bool mStuck;
		Block::BlockColor mColors[sNumBlocks];
		
		void updatePrivate(void);
		bool movePrivate(Direction);
		bool rotatePrivate(Rotation);
		bool hitOnMove(Direction) const;
		bool hitOnRotate(Rotation) const;
		void turnOn(void) const;
		void turnOff(void) const;
		void getMovementVariations(Direction, int&, int&) const;
		void getRotationVariation(Rotation, int&) const;
		Type getRandomType(void) const;
		Type convertIntToType(int) const;
		unsigned int getRandomRotation(void) const;

		Piece(void) {};
		Piece(const Piece&) {}
		const Piece& operator=(const Piece&) {}
	};
}