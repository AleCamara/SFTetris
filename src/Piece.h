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
			Count
		};

		// create a random piece at given board position
		Piece(const boost::shared_ptr<Board>&, unsigned int, unsigned int);

		virtual ~Piece(void) {}

		void setRow(int row) { mRow = row; }
		int getRow(void) const { return mRow; }
		void setColumn(int column) { mColumn = column; }
		int getColumn(void) const { return mColumn; }

		bool isStuck(void) const { return mStuck; }

		virtual void update(void);

	private:
		enum Direction
		{
			Down,
			Left,
			Right,
			Up
		};

		enum Rotation
		{
			CW,
			CCW
		};

		Type mType;
		unsigned int mNumBlocks;
		unsigned int mRotation;
		int mColumn, mRow;
		const boost::shared_ptr<Board> mBoard;
		bool mStuck;
		Block::BlockColor mColors[5];
	
		static const int RotationCount = 4;
		static const int BlockRow[Type::Count][RotationCount][5];
		static const int BlockColumn[Type::Count][RotationCount][5];
		
		void updatePrivate(void);
		void movePrivate(Direction);
		void rotatePrivate(Rotation);
		bool hit(void) const;
		bool hit(Direction) const;
		void turnOn(void) const;
		void turnOff(void) const;
		void setNumBlocks(void);
		void getMovementVariations(Direction, int&, int&) const;
		Type getRandomType(void) const;
		Type convertIntToType(int) const;
		unsigned int getRandomRotation(void) const;

		Piece(void) {};
		Piece(const Piece&) {}
		const Piece& operator=(const Piece&) {}
	};
}