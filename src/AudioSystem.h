#pragma once

#include "GameSystem.h"
#include <vector>
#include <boost\shared_ptr.hpp>
#include <SFML\Audio\Music.hpp>

namespace sm
{
	class AudioSystem: public GameSystem
	{
	public:
		AudioSystem(void);
		virtual ~AudioSystem(void) {}

		virtual void init(void) {}
		virtual void update(void) {}
		virtual void quit(void);

		void playMusic(void);
		void pauseMusic(void);
		void stopMusic(void);

		unsigned int createMusicPiece(void);
		void playMusicPiece(const unsigned int);
		boost::shared_ptr<sf::Music> getMusicPiece(const unsigned int);

	private:
		typedef std::vector<boost::shared_ptr<sf::Music>> MusicContainer;

		enum PlayingStatus
		{
			NotPlaying = -1
		};

		bool mPlayingMusic;
		int mCurrentMusic;
		MusicContainer mMusicPieces;

		bool checkIndex(const unsigned int) const;
	};
}