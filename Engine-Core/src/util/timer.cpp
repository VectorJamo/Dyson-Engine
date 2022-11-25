#include "Timer.h"

#include <GLFW/glfw3.h>

namespace ds {
	namespace util {

		float Timer::deltaTime = 0.0f;
		float Timer::lastTime = 0.0f;

		void Timer::ResetTimer()
		{
			lastTime = (float)glfwGetTime();
		}
		void Timer::CalculateDeltaTime()
		{
			deltaTime = glfwGetTime() - lastTime;
		}
		float Timer::GetDeltaTime()
		{
			return deltaTime;
		}
	}
}