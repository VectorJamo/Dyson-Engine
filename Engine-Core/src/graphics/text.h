#pragma once

#include <core.h>
#include <freetype/freetype.h>
#include <array>
#include <string>

#include "shader.h"
#include "data_buffers/vertex_array.h"
#include "data_buffers/vertex_buffer.h"
#include "data_buffers/index_buffer.h"
#include <util/error_handling.h>

namespace ds {
	namespace graphics {
		#define POS_BUFFER 0
		#define TCOORD_BUFFER 1
		#define TINDEX_BUFFER 2

		struct DS Character
		{
			unsigned int textureID;

			unsigned int bearingX, bearingY;
			unsigned int width, height;
			unsigned int advance;
		};

		class DS Text
		{
		private:
			std::array<Character, 128> pCharacters;
			static Shader* pShader;

			static FT_Library library;
			FT_Face face;

			VertexArray* pVAO;
			VertexBuffer* pVBO;
			IndexBuffer* pIBO;

			maths::vec2 pPosition, pTextSize;
			float pScale, pRotationAngle;
			maths::vec4 pColor;

			maths::mat4 pTranslation, pScaleMat, pRotation;

			Character pTextureUnits[32];
			int pTextLength;

		private:
			void BindTextures();

		public:
			Text(const char* fontFilePath, unsigned int fontSize);
			
			static void Init();
			static void Free();

			void LoadCharacters();
			void SetText(const std::string& text);
			void SetPosition(float x, float y);
			void SetScale(float scale);
			void SetRotation(float angle);
			void SetColor(float r, float g, float b, float a);
			void Render();
		};
	}
}

