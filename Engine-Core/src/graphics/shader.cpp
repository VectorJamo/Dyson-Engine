#include "shader.h"

namespace ds {
    namespace graphics {
        Shader::Shader(const std::string& vsPath, const std::string& fsPath)
            :pShaderProgram(0), pVertexShaderPath(vsPath), pFragmentShaderPath(fsPath), pVertexShaderCode(""), pFragmentShaderCode("")
        {
            pVertexShaderCode = ParseShader(vsPath);
            pFragmentShaderCode = ParseShader(fsPath);

            unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, pVertexShaderCode);
            unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, pFragmentShaderCode);

            pShaderProgram = glCreateProgram();
            glAttachShader(pShaderProgram, vertexShader);
            glAttachShader(pShaderProgram, fragmentShader);
            glLinkProgram(pShaderProgram);
            glValidateProgram(pShaderProgram);
        }

        Shader::~Shader()
        {
            glDeleteProgram(pShaderProgram);
        }

        std::string Shader::ParseShader(const std::string& filePath)
        {
            std::ifstream stream(filePath);
            std::string line, code;
            while (std::getline(stream, line))
            {
                code += (line + "\n");
            }
            return code;
        }

        unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& code)
        {
            unsigned int shader = glCreateShader(shaderType);
            const char* shaderCode = code.c_str();
            glShaderSource(shader, 1, &shaderCode, 0);
            glCompileShader(shader);

            // Error handling
            int status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                int length;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)_malloca(sizeof(char) * length);
                glGetShaderInfoLog(shader, length, &length, message);
                std::cout << ((shaderType == GL_VERTEX_SHADER) ? "|| Vertex-Shader Error: ||" : "|| Fragment-Shader Error ||") << std::endl;
                std::cout << message << std::endl;

                return -1;
            }
            else {
                return shader;
            }
        }

        void Shader::Bind()
        {
            glUseProgram(pShaderProgram);
        }
        void Shader::Unbind()
        {
            glUseProgram(0);
        }

        void Shader::SetUniform1f(const char* name, float value)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniform1f(location, value);
        }
        void Shader::SetUniform1i(const char* name, int value)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniform1i(location, value);
        }

        void Shader::SetUniform1iv(const char* name, int* value, int dataCount)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniform1iv(location, dataCount, value);
        }

        void Shader::SetUniformVec2f(const char* name, const maths::vec2& vec)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniform2fv(location, 1, &vec.x);
        }

        void Shader::SetUniformVec4f(const char* name, const maths::vec4& vec)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniform2fv(location, 1, &vec.x);
        }

        void Shader::SetUniformMat4f(const char* name, const maths::mat4& matrix)
        {
            int location = glGetUniformLocation(pShaderProgram, name);
            if (location < 0)
                std::cout << "Uniform : " << name << " doesnot exist or is not in use" << std::endl;
            else
                glUniformMatrix4fv(location, 1, GL_TRUE, &matrix[0][0]);
        }
    }
}