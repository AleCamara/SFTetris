#include "Board.h"

#include <SFML\Graphics\RenderTarget.hpp>
#include "Game.h"
#include "Logger.h"

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

	void Board::activateBlock(const unsigned int i, const unsigned int j, const Block::BlockColor& color)
	{
		if(checkIndex(i, j))
		{
			mBlocks.at(getIndex(i, j))->activate(color);
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
		for(int k=0; k<(int)mBlocks.size(); ++k)
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
			for(int currentCol=0; currentCol<(int)mSizeJ; ++currentCol)
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
		checkHorizontalColors();
		checkVerticalColors();
		deleteMarkedBlocks();
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
		for(int col=0; col<(int) mSizeJ; ++col)
		{
			deactivateBlock(row, col);
		}
	}

	void Board::moveRowsDown(const unsigned int startRow)
	{
		moveRowsDown(startRow, 0, mSizeJ-1);
	}

	void Board::moveRowsDown(const unsigned int startRow, const unsigned int startColumn,
		const unsigned int endColumn)
	{
		// notice that does not make sense to move from row -1 to row 0
		//                       V
		for(int row=startRow; row>0; --row)
		{
			for(int col=(int)startColumn; col<=(int)endColumn; ++col)
			{
				mBlocks.at(getIndex(row, col))->copyFrom(*mBlocks.at(getIndex(row-1, col)));
				
				// row 0 must be deactivated
				if(row==1)
				{
					deactivateBlock(0, col);
				}
			}
		}
	}

	void Board::checkHorizontalColors(void)
	{
		for(int row=mSizeI-1; row>=0; --row)
		{
			int startColumn = 0;
			int endColumn = 1;
			int numMatches = 1;
			Block::BlockColor curColor = mBlocks.at(getIndex(row, startColumn))->getColor();
			Block::BlockColor iterColor = curColor;
			while(endColumn < (int) mSizeJ)
			{
				iterColor = mBlocks.at(getIndex(row, endColumn))->getColor();
				if(curColor == iterColor)
				{
					numMatches++;
				}
				
				// possible block deletion
				if((curColor != iterColor || endColumn == mSizeJ-1)
					&& numMatches >= sMinCoincidencesToDelete
					&& curColor != Block::Grey)
				{
					Game::instance()->getLogger()->getBuffer() << "Horizonal block deletion at row "
						<< row << " from column " << startColumn << " to " << endColumn << ". Total of "
						<< numMatches << " matches.";
					Game::instance()->getLogger()->debug(5);

					if(curColor == iterColor)
					{
						markHorizontal(row, startColumn, endColumn);
					}
					else
					{
						markHorizontal(row, startColumn, endColumn-1);
					}

					startColumn = endColumn;
					curColor = iterColor;
					numMatches = 1;
				}

				if(curColor != iterColor)
				{
					startColumn = endColumn;
					curColor = iterColor;
					numMatches = 1;
				}

				endColumn++;
			}
		}
	}

	void Board::checkVerticalColors(void)
	{
		for(int col=0; col<(int)mSizeJ; ++col)
		{
			int startRow = mSizeI-1;
			int endRow = mSizeI-2;
			int numMatches = 1;
			Block::BlockColor curColor = mBlocks.at(getIndex(startRow, col))->getColor();
			Block::BlockColor iterColor = curColor;
			while(endRow >= 0)
			{
				iterColor = mBlocks.at(getIndex(endRow, col))->getColor();
				if(curColor == iterColor)
				{
					numMatches++;
				}
				
				// possible block deletion
				if((curColor != iterColor || endRow == 0)
					&& numMatches >= sMinCoincidencesToDelete
					&& curColor != Block::Grey)
				{
					Game::instance()->getLogger()->getBuffer() << "Vertical block deletion at column "
						<< col << " from row " << startRow << " to " << endRow+1 << ". Total of "
						<< numMatches << " matches.";
					Game::instance()->getLogger()->debug(5);

					if(curColor == iterColor)
					{
						markVertical(col, startRow, endRow);
					}
					else
					{
						markVertical(col, startRow, endRow+1);
					}

					startRow = endRow;
					curColor = iterColor;
					numMatches = 1;
				}

				if(curColor != iterColor)
				{
					startRow = endRow;
					curColor = iterColor;
					numMatches = 1;
				}

				endRow--;
			}
		}
	}

	void Board::markHorizontal(const unsigned int row, const unsigned int startColumn,
		const unsigned int endColumn)
	{
		for(int col=startColumn; col<=(int)endColumn; ++col)
		{
			if(checkIndex(row, col))
			{
				mBlocks.at(getIndex(row, col))->markForDeletion();
			}
		}
	}

	void Board::markVertical(const unsigned int col, const unsigned int startRow,
		const unsigned int endRow)
	{
		for(int row=startRow; row>=(int)endRow; --row)
		{
			if(checkIndex(row, col))
			{
				mBlocks.at(getIndex(row, col))->markForDeletion();
			}
		}
	}

	void Board::deleteMarkedBlocks(void)
	{
		for(int row=0; row<(int)mSizeI; ++row)
		{
			for(int col=0; col<(int)mSizeJ; ++col)
			{
				if(mBlocks.at(getIndex(row, col))->isMarkedForDeletion())
				{
					moveRowsDown(row, col, col);
				}
			}
		}
	}
}