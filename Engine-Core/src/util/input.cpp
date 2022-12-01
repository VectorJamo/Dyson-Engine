#include "Input.h"

namespace ds {
	namespace util {

		graphics::Window* Input::pWindow;
		bool Input::pKeys[NUM_KEYS];
		bool Input::pMouseButtons[NUM_MOUSE_BUTTONS];
		bool Input::pScrollUp;
		bool Input::pScrollDown;
		maths::vec2 Input::pMousePos;
		maths::vec2 Input::pMouseDeltaPos;

		void Input::Init(graphics::Window* window)
		{
			pWindow = window;
			memset(pKeys, 0, sizeof(bool) * NUM_KEYS);
			glfwSetKeyCallback(window->GetWindowObject(), key_callback);

			glfwSetMouseButtonCallback(window->GetWindowObject(), mouse_button_callback);
			glfwSetScrollCallback(window->GetWindowObject(), scroll_callback);

			#if _DEBUG
				std::cout << " -> Input System Initialized!" << std::endl;
			#endif
		}

		bool Input::IsKeyPressed(int keyCode)
		{
			if (pKeys[keyCode])
			{
				pKeys[keyCode] = false;
				return true;
			}
			return false;
		}
		bool Input::IsKeyHold(int keyCode)
		{
			return pKeys[keyCode];
		}

		bool Input::IsMouseButtonPressed(int buttonCode)
		{
			if (pMouseButtons[buttonCode])
			{
				pMouseButtons[buttonCode] = false;
				return true;
			}
			return false;
		}

		bool Input::IsMouseButtonHold(int buttonCode)
		{
			return pMouseButtons[buttonCode];
		}

		bool Input::IsMouseScrollUp()
		{
			if (pScrollUp)
			{
				pScrollUp = false;
				return true;
			}
			return false;
		}

		bool Input::IsMouseScrollDown()
		{
			if (pScrollDown)
			{
				pScrollDown = false;
				return true;
			}
			return false;
		}

		void Input::Update()
		{
			// Calculate delta mouse posisiton
			double mouseX, mouseY;
			glfwGetCursorPos(pWindow->GetWindowObject(), &mouseX, &mouseY);
			pMouseDeltaPos.x = (float)mouseX - pMousePos.x;
			pMouseDeltaPos.y = (float)mouseY - pMousePos.y;

			pMousePos.x = (float)mouseX;
			pMousePos.y = (float)mouseY;
		}

		void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
				pKeys[key] = true;
			if (action == GLFW_RELEASE)
				pKeys[key] = false;
		}
		void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
				pMouseButtons[button] = true;
			if (action == GLFW_RELEASE)
				pMouseButtons[button] = false;
		}

		void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (yoffset == 1)
			{
				pScrollUp = true;
				pScrollDown = false;
			}
			if (yoffset == -1)
			{
				pScrollDown = true;
				pScrollUp = false;
			}
		}
	}
}