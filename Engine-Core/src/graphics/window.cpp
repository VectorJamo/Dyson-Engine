#include "window.h"

#include "util/timer.h"
#include "graphics/sprite.h"
#include "util/input.h"
#include "graphics/batch_renderer.h"
#include "util/orthographic_camera.h"

#include "util/error_handling.h"
#include "graphics/text.h"
#include "util/audio.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ds {
    namespace graphics {
        Shader* Window::pShader;
        static unsigned int gWidth, gHeight;

        Window::Window(int width, int height, const char* title)
            :pWindow(nullptr), pTitle(title), pLineVAO(0), pLineVBO(0), pPointVAO(0), pPointVBO(0)
        {
            gWidth = width;
            gHeight = height;
        }

        Window::~Window()
        {
            delete pShader;

            Sprite::Free();
            BatchRenderer::Free();
            Text::Free();

            glfwTerminate();
        }
        void Window::Init()
        {
            if (!glfwInit())
                THROW_ERROR("Failed to initialize GLFW!");

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            pWindow = glfwCreateWindow(gWidth, gHeight, pTitle, NULL, NULL);
            if (pWindow == nullptr)
                THROW_ERROR("Failed to create GLFW window!");

            glfwMakeContextCurrent(pWindow);
            glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

            if (glewInit() != GLEW_OK)
                THROW_ERROR("Failed to initialize GLEW!");

            // Enable blending by default
            EnableBlend(true);
            SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // Create the buffers for lines and point rendering
            // Line VAO and VBO
            glGenVertexArrays(1, &pLineVAO);
            glBindVertexArray(pLineVAO);

            glGenBuffers(1, &pLineVBO);
            glBindBuffer(GL_ARRAY_BUFFER, pLineVBO);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(maths::vec2), 0);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Point VAO and VBO
            glGenVertexArrays(1, &pPointVAO);
            glBindVertexArray(pPointVAO);

            glGenBuffers(1, &pPointVBO);
            glBindBuffer(GL_ARRAY_BUFFER, pPointVBO);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(maths::vec2), 0);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Create the shaders
            const char* vsCode = R"(
                #version 330 core
                
                layout(location = 0) in vec2 position;
                
                uniform mat4 uTranslationToOrigin;
                uniform mat4 uTranslationToOriginal;
                
                uniform mat4 uRotation;
                
                uniform mat4 uCameraTranslation;
                uniform mat4 uCameraRotation;
                
                uniform mat4 uProjection;
                
                void main()
                {
                	gl_Position =  uProjection * uCameraTranslation * uTranslationToOriginal * uCameraRotation * uRotation * uTranslationToOrigin * vec4(position.x, position.y, 0.0f, 1.0f);
                }
            )";
            const char* fsCode = R"(
                #version 330 core
                
                out vec4 fragColor;
                
                uniform vec4 uColor;
                
                void main()
                {
                	fragColor = uColor;
                }
            )";

            pShader = new Shader(vsCode, fsCode, true);

            // Initialize the systems
            util::Input::Init(this);
            Sprite::Init();
            BatchRenderer::Init();
            util::OrthographicCamera::Init(-(int)(gWidth / 2), gWidth / 2, gHeight / 2, -(int)(gHeight / 2), 1.0f, -1.0f);
            Text::Init();
            util::Audio::Init();
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
        void Window::Clear()
        {
            util::Timer::ResetTimer();

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
            util::Input::Update();
        }

        void Window::DrawLine(const maths::vec2& point1, const maths::vec2& point2, const maths::vec4 color, int rotationAngle)
        {
            maths::vec2 positions[2] =
            {
                point1, point2
            };

            maths::vec2 midPoint = point1.GetMidPoint(point2);
            maths::mat4 translationToOrigin = maths::translate(maths::vec3(-midPoint.x, -midPoint.y, 0.0f));
            maths::mat4 translationToOriginal = maths::translate(maths::vec3(midPoint.x, midPoint.y, 0.0f));
            maths::mat4 rotationMatrix = maths::rotate(-TO_RADIANS(rotationAngle), maths::vec3(0.0f, 0.0f, 1.0f));

            glBindBuffer(GL_ARRAY_BUFFER, pLineVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(maths::vec2) * 2, positions, GL_STATIC_DRAW);

            glBindVertexArray(pLineVAO);
            pShader->Bind();
            pShader->SetUniformVec4f("uColor", color);

            pShader->SetUniformMat4f("uTranslationToOrigin", translationToOrigin);
            pShader->SetUniformMat4f("uTranslationToOriginal", translationToOriginal);
            pShader->SetUniformMat4f("uRotation", rotationMatrix);

            pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());
            pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
            pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());

            glDrawArrays(GL_LINES, 0, 2);
        }

        void Window::DrawDot(const maths::vec2& point, const maths::vec4& color)
        {
            glBindBuffer(GL_ARRAY_BUFFER, pPointVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(maths::vec2), &point, GL_STATIC_DRAW);

            glBindVertexArray(pPointVAO);
            pShader->Bind();

            pShader->SetUniformVec4f("uColor", color);

            maths::mat4 identity(1.0f);

            pShader->SetUniformMat4f("uTranslationToOrigin", identity);
            pShader->SetUniformMat4f("uTranslationToOriginal", identity);
            pShader->SetUniformMat4f("uRotation", identity);

            pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
            pShader->SetUniformMat4f("uCameraRotation", identity);

            pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

            glDrawArrays(GL_POINTS, 0, 1);
        }

        void Window::SetClearColor(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
        }

        void Window::SetVSyncEnabled(bool status)
        {
            glfwSwapInterval(status);
        }

        void Window::SetSize(int width, int height)
        {
            glfwSetWindowSize(pWindow, width, height);
            gWidth = width;
            gHeight = height;
        }

        void Window::SetTitle(const char* title)
        {
            glfwSetWindowTitle(pWindow, title);
        }

        void Window::SetShouldClose(bool status)
        {
            glfwSetWindowShouldClose(pWindow, status);
        }

        unsigned int Window::GetWidth()
        {
            return gWidth;
        }
        unsigned int Window::GetHeight()
        {
            return gHeight;
        }

        void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            gWidth = width;
            gHeight = height;
            glViewport(0, 0, width, height);
        }
    }
}