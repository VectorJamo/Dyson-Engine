#include "Input.h"

namespace ds {
	namespace util {

		graphics::Window* Input::window;
		bool Input::keys[NUM_KEYS];
		bool Input::mouseButtons[NUM_MOUSE_BUTTONS];
		bool Input::scrollUp;
		bool Input::scrollDown;
		maths::vec2 Input::mousePos;
		maths::vec2 Input::mouseDeltaPos;

		void Input::Init(graphics::Window* window)
		{
			window = window;
			memset(keys, 0, sizeof(bool) * NUM_KEYS);
			glfwSetKeyCallback(window->GetWindowObject(), key_callback);

			glfwSetMouseButtonCallback(window->GetWindowObject(), mouse_button_callback);
			glfwSetScrollCallback(window->GetWindowObject(), scroll_callback);
		}

		bool Input::IsKeyPressed(int keyCode)
		{
			if (keys[keyCode])
			{
				keys[keyCode] = false;
				return true;
			}
			return false;
		}
		bool Input::IsKeyHold(int keyCode)
		{
			return keys[keyCode];
		}

		bool Input::IsMouseButtonPressed(int buttonCode)
		{
			if (mouseButtons[buttonCode])
			{
				mouseButtons[buttonCode] = false;
				return true;
			}
			return false;
		}

		bool Input::IsMouseButtonHold(int buttonCode)
		{
			return mouseButtons[buttonCode];
		}

		bool Input::IsMouseScrollUp()
		{
			if (scrollUp)
			{
				scrollUp = false;
				return true;
			}
			return false;
		}

		bool Input::IsMouseScrollDown()
		{
			if (scrollDown)
			{
				scrollDown = false;
				return true;
			}
			return false;
		}

		void Input::Update()
		{
			// Calculate delta mouse posisiton
			double mouseX, mouseY;
			glfwGetCursorPos(window->GetWindowObject(), &mouseX, &mouseY);
			mouseDeltaPos.x = (float)mouseX - mousePos.x;
			mouseDeltaPos.y = (float)mouseY - mousePos.y;

			mousePos.x = (float)mouseX;
			mousePos.y = (float)mouseY;
		}

		void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
				keys[key] = true;
			if (action == GLFW_RELEASE)
				keys[key] = false;
		}
		void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
				mouseButtons[button] = true;
			if (action == GLFW_RELEASE)
				mouseButtons[button] = false;
		}

		void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (yoffset == 1)
			{
				scrollUp = true;
				scrollDown = false;
			}
			if (yoffset == -1)
			{
				scrollDown = true;
				scrollUp = false;
			}
		}
	}
}