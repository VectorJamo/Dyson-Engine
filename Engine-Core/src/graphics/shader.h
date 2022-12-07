#pragma once
#include "../core.h"
#include <string>

#include "../maths/vec/vec2.h"
#include "../maths/vec/vec4.h"
#include "../maths/mat/mat4.h"

namespace ds {
    namespace graphics {
        class DS Shader
        {
        private:
            unsigned int pShaderProgram;
            std::string pVertexShaderPath, pFragmentShaderPath;
            std::string pVertexShaderCode, pFragmentShaderCode;

        private:
            std::string ParseShader(const std::string& filePath);
            unsigned int CompileShader(unsigned int shaderType, const std::string& shaderCode);

        public:
            Shader(const char* vsPath, const char* fsPath);
            Shader(const std::string& vsCode, const std::string& fsCode, bool inCode); // <- A pseudo bool to distinguish between two Shader constructors
            ~Shader();

            void Bind();
            void Unbind();

            void SetUniform1f(const char* name, float value);
            void SetUniform1i(const char* name, int value);
            void SetUniform1iv(const char* name, int* value, int dataCount);

            void SetUniformVec2f(const char* name, const maths::vec2& vec);
            void SetUniformVec4f(const char* name, const maths::vec4& vec);
            void SetUniformMat4f(const char* name, const maths::mat4& matrix);
        };

    }
}
