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
			return mBlocks.at(getIndex(i, j))->checkActive();
		}
		// should be an exception?
		return false;
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

	unsigned int Board::getIndex(unsigned int i, unsigned int j) const
	{
		return (i*mSizeJ + j);
	}

	bool Board::checkIndex(unsigned int i, unsigned int j) const
	{
		return (i < mSizeI && j < mSizeJ);
	}
}