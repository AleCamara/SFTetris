#include "Board.h"

#include <SFML\Graphics\RenderTarget.hpp>

namespace sm
{
	Board::Board(const unsigned int i, const unsigned int j)
		: mSizeI(i), mSizeJ(j), mBlocks()
	{
		for(unsigned int i=0; i<mSizeI; ++i)
		{
			for(unsigned int j=0; j<mSizeJ; ++j)
			{
				boost::shared_ptr<Block> block(new Block());
				block->setPosition(j*(Block::SIZE + Block::PADDING), i*(Block::SIZE + Block::PADDING));
				mBlocks.push_back(block);
			}
		}
	}

	Board::~Board(void) {}

	void Board::activateBlock(const unsigned int i, const unsigned int j)
	{
		if(checkIndex(i, j))
		{
			mBlocks.at(getIndex(i, j))->activate();
		}
	}

	void Board::deactivateBlock(const unsigned int i, const unsigned int j)
	{
		if(checkIndex(i, j))
		{
			mBlocks.at(getIndex(i, j))->deactivate();
		}
	}

	void Board::resetBlocks(void)
	{
		for(int k=0; k<mBlocks.size(); ++k)
		{
			mBlocks.at(k)->deactivate();
		}
	}

	void Board::changeBlockColor(const unsigned int i, const unsigned int j, Block::BlockColor color)
	{
		if(checkIndex(i, j))
		{
			mBlocks.at(getIndex(i, j))->setColor(color);
		}
	}

	bool Board::checkBoardPosition(const unsigned int i, const unsigned int j) const
	{
		if(checkIndex(i, j))
		{
			return mBlocks.at(getIndex(i, j))->isActive();
		}
		// should be an exception?
		return false;
	}

	void Board::checkHorizontal(void)
	{
		bool fullRow = true;
		for(int currentRow=mSizeI-1; currentRow>=0; --currentRow)
		{
			fullRow = true;
			for(int currentCol=0; currentCol<mSizeJ; ++currentCol)
			{
				if(!checkBoardPosition(currentRow, currentCol))
				{
					fullRow = false;
					break;
				}
			}

			if(fullRow)
			{
				// turn off row
				turnOffRow(currentRow);

				// move rows down
				moveRowsDown(currentRow);

				// recheck current row
				++currentRow;
			}
		}
	}

	void Board::checkColors(void)
	{
	}

	void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		BlockContainerType::const_iterator iter = mBlocks.cbegin();
		for(; iter != mBlocks.cend(); ++iter) 
		{
			target.draw(*(*iter).get(), states);
		}
	}

	unsigned int Board::getIndex(const unsigned int i, const unsigned int j) const
	{
		return (i*mSizeJ + j);
	}

	bool Board::checkIndex(const unsigned int i, const unsigned int j) const
	{
		return (i < mSizeI && j < mSizeJ);
	}

	void Board::turnOffRow(const unsigned int row)
	{
		for(int col=0; col<mSizeJ; ++col)
		{
			deactivateBlock(row, col);
		}
	}

	void Board::moveRowsDown(const unsigned int startingRow)
	{
		// notice that does not make sense to move from row -1 to row 0
		//                          V
		for(int row=startingRow; row>0; --row)
		{
			for(int col=0; col<mSizeJ; ++col)
			{
				mBlocks.at(getIndex(row, col))->copyFrom(*mBlocks.at(getIndex(row-1, col)));
			}
		}
	}
}