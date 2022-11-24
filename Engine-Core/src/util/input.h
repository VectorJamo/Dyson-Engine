#pragma once
#include "KeyCodes.h"
#include "maths/vec/vec2.h"
#include "maths/vec/vec4.h"
#include "maths/mat/mat4.h"
#include "graphics/window.h"

#include <iostream>

#define NUM_KEYS 350
#define NUM_MOUSE_BUTTONS 9

namespace ds {
	namespace util {
		class DS Input
		{
		private:
			static graphics::Window* window;
			static bool keys[NUM_KEYS];
			static bool mouseButtons[NUM_MOUSE_BUTTONS];
			static bool scrollUp;
			static bool scrollDown;
			static maths::vec2 mousePos;
			static maths::vec2 mouseDeltaPos;

		public:
			static void Init(graphics::Window* window);
			static bool IsKeyPressed(int keyCode);
			static bool IsKeyHold(int keyCode);

			static bool IsMouseButtonPressed(int buttonCode);
			static bool IsMouseButtonHold(int buttonCode);

			static bool IsMouseScrollUp();
			static bool IsMouseScrollDown();

			static void Update();

			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

			static inline maths::vec2 GetMousePos() { return mousePos; }
			static inline maths::vec2 GetMouseDeltaPos() { return mouseDeltaPos; }
		};
	}
}
