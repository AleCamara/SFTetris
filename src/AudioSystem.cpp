#include "AudioSystem.h"

namespace sm
{
	AudioSystem::AudioSystem(void)
		: mPlayingMusic(false), mCurrentMusic(NotPlaying), mMusicPieces()
	{
	}

	void AudioSystem::quit(void)
	{
		stopMusic();
	}

	void AudioSystem::playMusic(void)
	{
		if(checkIndex(mCurrentMusic))
		{
			mMusicPieces.at(mCurrentMusic)->play();
		}
	}

	void AudioSystem::pauseMusic(void)
	{

		if(checkIndex(mCurrentMusic))
		{
			mMusicPieces.at(mCurrentMusic)->pause();
		}
	}

	void AudioSystem::stopMusic(void)
	{
		if(checkIndex(mCurrentMusic))
		{
			mMusicPieces.at(mCurrentMusic)->stop();
		}
	}

	unsigned int AudioSystem::createMusicPiece(void)
	{
		mMusicPieces.push_back(boost::shared_ptr<sf::Music>(new sf::Music()));
		return mMusicPieces.size()-1;
	}

	void AudioSystem::playMusicPiece(const unsigned int key)
	{
		if(checkIndex(key))
		{
			stopMusic();
			mCurrentMusic = key;
			mMusicPieces.at(key)->play();
		}
	}

	boost::shared_ptr<sf::Music> AudioSystem::getMusicPiece(const unsigned int key)
	{
		if(checkIndex(key))
		{
			return mMusicPieces.at(key);
		}
		throw std::out_of_range("Music piece is not existant.");
	}

	bool AudioSystem::checkIndex(const unsigned int key) const
	{
		return (key < mMusicPieces.size());
	}
}