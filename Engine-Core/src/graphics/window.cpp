#include "window.h"

#include "util/timer.h"
#include "graphics/sprite.h"
#include "util/input.h"
#include "graphics/batch_renderer.h"
#include "util/orthographic_camera.h"

#include "util/error_handling.h"

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
        void Window::Init()
        {
            if (!glfwInit())
                THROW_ERROR("Failed to initialize GLFW!");

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            pWindow = glfwCreateWindow(pWidth, pHeight, pTitle, NULL, NULL);
            if (pWindow == nullptr)
                THROW_ERROR("Failed to create GLFW window!");

            glfwMakeContextCurrent(pWindow);
            glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

            if (glewInit() != GLEW_OK)
                THROW_ERROR("Failed to initialize GLEW!");

            // Initialize the systems
            util::Input::Init(this);
            Sprite::Init();
            BatchRenderer::Init();
            util::OrthographicCamera::Init(-pWidth/2, pWidth/2, pHeight/2, -pHeight/2, 1.0f, -1.0f);

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
            util::Timer::ResetTimer();

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

            util::Timer::CalculateDeltaTime();
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