#pragma once
#include <core.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

namespace ds { 
	namespace graphics {

        class DS Window
        {
        private:
            GLFWwindow* pWindow;
            const char* pTitle;
                
            unsigned int pLineVAO, pLineVBO;
            unsigned int pPointVAO, pPointVBO;
            static Shader* pShader;

        public:
            Window(int width, int height, const char* title);
            ~Window();

            void Init();
            bool IsClosed();
            void SetBlendFunction(int srcFactor, int dstFactor);
            void SetBlendEquation(unsigned int mode);
            void EnableBlend(bool status);

            void PollEvents();
            void Clear(float r, float g, float b, float a);
            void Display();

            void DrawLine(const maths::vec2& point1, const maths::vec2& point2, const maths::vec4 color, int rotationAngle);
            void DrawDot(const maths::vec2& point, const maths::vec4& color);

            // Setters
            void SetVSyncEnabled(bool status);

            // Getters
            static unsigned int GetWidth();
            static unsigned int GetHeight();

            inline GLFWwindow* GetWindowObject() const { return pWindow; }
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        };

	}
}