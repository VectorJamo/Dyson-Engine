#pragma once

#include "../core.h"

#include <iostream>

namespace irrklang
{
	extern class ISoundSource;
	extern class ISound;
}

namespace ds {
	namespace util {

		class DS Audio
		{
		public:
			static void Init();
			static void Free();
		};

		class DS Music
		{
		private:
			irrklang::ISoundSource* pSource;
			irrklang::ISound* pSound;
			bool pIsMusicBeingPlayed;

		public:
			Music(const char* filePath);
			~Music();

			void Play(bool loop);
			void Stop();
			void Pause();
			void Resume();

			void SetDefaultVolume(float volume = 1.0f);
			void SetVolume(float volume = 1.0f);
		};

		class DS SoundEffect
		{
		private:
			irrklang::ISoundSource* pSource;
			irrklang::ISound* pSound;

		public:
			SoundEffect(const char* filePath);
			~SoundEffect();

			void Play();
			void SetDefaultVolume(float volume = 1.0f);
		};

	}
}

