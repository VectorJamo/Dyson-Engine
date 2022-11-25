#pragma once
#include "core.h"

namespace ds {
	namespace util {
		class DS Timer
		{
		private:
			static float deltaTime;
			static float lastTime;

		public:
			Timer() = delete;

			static void ResetTimer();
			static void CalculateDeltaTime();

			static float GetDeltaTime();
		};
	}
}
