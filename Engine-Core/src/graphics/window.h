#pragma once
#include <iostream>
#include <core.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ds { 
	namespace graphics {
        extern int gWidth, gHeight;
        class DS Window
        {
        private:
            GLFWwindow* pWindow;
            int pWidth, pHeight;
            const char* pTitle;

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

            // Setters
            void SetVSyncEnabled(bool status);

            // Getters
            inline int GetWidth() const { return pWidth; }
            inline int GetHeight() const { return pHeight; }

            inline GLFWwindow* GetWindowObject() const { return pWindow; }
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        };

	}
}