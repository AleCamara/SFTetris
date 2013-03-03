#pragma once

#include <vector>
#include <boost\shared_ptr.hpp>
#include "Entity.h"
#include "Block.h"

namespace sm
{
	class Board: public Entity
	{
	public:
		Board(const unsigned int, const unsigned int);
		virtual ~Board(void);

		void activateBlock(const unsigned int, const unsigned int);
		void deactivateBlock(const unsigned int, const unsigned int);
		void resetBlocks(void);
		void changeBlockColor(const unsigned int, const unsigned int, Block::BlockColor);

		unsigned int getNumRows(void) const { return mSizeI; }
		unsigned int getNumColumns(void) const {return mSizeJ; }

		bool checkBoardPosition(const unsigned int, const unsigned int) const;

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		typedef std::vector<boost::shared_ptr<Block>> BlockContainerType;
		
		const unsigned int mSizeI;
		const unsigned int mSizeJ;

		BlockContainerType mBlocks;

		unsigned int getIndex(unsigned int, unsigned int) const;
		bool checkIndex(unsigned int, unsigned int) const;
	};
}