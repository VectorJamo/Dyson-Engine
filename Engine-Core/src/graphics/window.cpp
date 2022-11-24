#include "window.h"

namespace ds {
	namespace graphics {
        int gWidth, gHeight;
        Window::Window(int width, int height, const char* title)
            :pWindow(nullptr), pTitle(title)
        {
            pWidth = width;
            pHeight = height;
        }

        Window::~Window()
        {
            glfwTerminate();
        }
        bool Window::Init()
        {
            if (!glfwInit())
            {
                std::cout << "Failed to initialize GLFW!" << std::endl;
                return false;
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            pWindow = glfwCreateWindow(pWidth, pHeight, pTitle, NULL, NULL);
            if (pWindow == nullptr)
            {
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }
            glfwMakeContextCurrent(pWindow);
            glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
            if (glewInit() != GLEW_OK)
            {
                std::cout << "Failed to initialize GLEW!" << std::endl;
                return false;
            }
            return true;
        }
        bool Window::IsClosed()
        {
            return glfwWindowShouldClose(pWindow);
        }
        void Window::SetBlendFunction(int srcFactor, int dstFactor)
        {
            glBlendFunc(srcFactor, dstFactor);
        }
        void Window::SetBlendEquation(unsigned int mode)
        {
            glBlendEquation(mode);
        }
        void Window::EnableBlend(bool status)
        {
            status ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        }
        void Window::Clear(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        void Window::PollEvents()
        {
            glfwPollEvents();
        }
        void Window::Display()
        {
            glfwSwapBuffers(pWindow);
        }
        void Window::SetVSyncEnabled(bool status)
        {
            glfwSwapInterval(status);
        }

        void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            gWidth = width;
            gHeight = height;
            glViewport(0, 0, width, height);
        }
	}
}