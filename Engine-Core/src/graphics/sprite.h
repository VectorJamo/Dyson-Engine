#pragma once

#include "shader.h"
#include "texture.h"

#include "../maths/constants.h"

#include "data_buffers/vertex_array.h"
#include "data_buffers/vertex_buffer.h"
#include "data_buffers/index_buffer.h"

#include "tilemap.h"
namespace ds {
	namespace graphics {
		class DS Sprite
		{
		private:
			// Sprite's data
			VertexArray* pVAO;
			VertexBuffer* pVBO;
			VertexBuffer* pVBO2;
			IndexBuffer* pIBO;
			static Shader* pShader;

			bool pUsesTexture;
			Texture* pTexture;
			unsigned int pTextureUnit;

			// Sprite's transform
			maths::vec2 pPosition, pSize;
			maths::vec4 pColor;

			// Sprite's transform matrices
			maths::mat4 pTranslation, pRotation, pScale;

		private:
			void CreateRect();

		public:
			Sprite(float x, float y, float width, float height);
			~Sprite();

			void Draw();
			void Draw(Shader* shader);

			static void Init();
			static void Free();

			bool IsCollided(const Sprite* sprite);
			bool IsCollided(const Tile* tile);
			bool IsCollided(const Tile* tile, float& dx, float& dy);

			// Setters
			void SetTexture(const char* texturePath);
			void SetTexture(Texture* texture);
			void SetPosition(float x, float y);
			void SetSize(float width, float height);
			void SetRotation(float angle);
			void SetColor(const maths::vec4& color);
			void SetTextureClipRect(int x, int y, int width, int height);

			// Getters
			inline maths::vec2 GetPosition() const { return pPosition; }
			inline maths::vec2 GetSize() const { return pSize; }
			inline maths::vec4 GetColor() const { return pColor; }
		};
	}
}
