#include "audio.h"

namespace ds {
	namespace util {

		static irrklang::ISoundEngine* gSoundEngine;

		void Audio::Init()
		{
			gSoundEngine = irrklang::createIrrKlangDevice();
		}
		void Audio::Free()
		{
			gSoundEngine->drop();
		}



		Music::Music(const std::string& filePath)
			:pSource(nullptr), pSound(nullptr), pIsMusicBeingPlayed(false)
		{
			pSource = gSoundEngine->addSoundSourceFromFile(filePath.c_str());
		}

		Music::~Music()
		{
			if (pSound != nullptr)
				pSound->drop();
		}

		void Music::Play(bool loop)
		{
			if (!pIsMusicBeingPlayed)
			{
				if (pSound != nullptr)
					pSound->drop();

				pSound = gSoundEngine->play2D(pSource, loop, false, true, false);

				pIsMusicBeingPlayed = true;
			}
		}

		void Music::Stop()
		{
			if (pIsMusicBeingPlayed)
			{
				pSound->stop();
				pIsMusicBeingPlayed = false;
			}
		}

		void Music::Pause()
		{
			if (pIsMusicBeingPlayed)
			{
				pSound->setIsPaused(true);
				pIsMusicBeingPlayed = false;
			}
		}
		void Music::Resume()
		{
			if (!pIsMusicBeingPlayed)
			{
				pSound->setIsPaused(false);
				pIsMusicBeingPlayed = true;
			}
		}

		void Music::SetVolume(float volume)
		{
			if(pIsMusicBeingPlayed)
				pSound->setVolume(volume);
		}
		void Music::SetDefaultVolume(float volume)
		{
			pSource->setDefaultVolume(volume);
		}


		SoundEffect::SoundEffect(const std::string& filePath)
			:pSource(nullptr), pSound(nullptr)
		{
			pSource = gSoundEngine->addSoundSourceFromFile(filePath.c_str());
		}

		SoundEffect::~SoundEffect()
		{
			if (pSound != nullptr)
				pSound->drop();
		}

		void SoundEffect::Play()
		{
			pSound = gSoundEngine->play2D(pSource);
		}

		void SoundEffect::SetDefaultVolume(float volume)
		{
			pSource->setDefaultVolume(volume);
		}

	}
}

