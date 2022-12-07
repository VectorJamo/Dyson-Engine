#include "text.h"
#include <freetype/freetype.h>

#include <util/orthographic_camera.h>
#include "maths/constants.h"

#include <GL/glew.h>

namespace ds {
	namespace graphics {
		Shader* Text::pShader;
		FT_Library Text::library;

		Text::Text(const char* fontFilePath, unsigned int fontSize)
			:pVAO(nullptr), pVBO(nullptr), pIBO(nullptr), pScale(1.0f), pRotationAngle(0), pTextLength(0)
		{
#if _DEBUG

			// Load the font
			if (FT_New_Face(library, fontFilePath, 0, &face) != 0)
				THROW_ERROR("Failed to load font!");
#else 
			FT_New_Face(library, fontFilePath, 0, &face);
#endif

			FT_Set_Pixel_Sizes(face, 0, fontSize);

			// Create the buffers, allocate the memeory and set the buffer layout 
			pVAO = new VertexArray();

			pVBO = new VertexBuffer[3];
			pVBO[POS_BUFFER].Bind();
			pVBO[POS_BUFFER].SendData(sizeof(float) * 8 * 32, 0);

			pVBO[TCOORD_BUFFER].Bind();
			pVBO[TCOORD_BUFFER].SendData(sizeof(float) * 8 * 32, 0);

			pVBO[TINDEX_BUFFER].Bind();
			pVBO[TINDEX_BUFFER].SendData(sizeof(float) * 4 * 32, 0);

			pIBO = new IndexBuffer(sizeof(unsigned short) * 6 * 32, 0);

			pVAO->Bind();

			pVBO[POS_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);
			pVBO[TCOORD_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);
			pVBO[TINDEX_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 1, sizeof(float), 0);

			pIBO->Bind();

			pVAO->Unbind();

			memset(pTextureUnits, 0, sizeof(Character) * 32);

			LoadCharacters();
		}
		Text::~Text()
		{
			delete pVAO;
			delete[] pVBO;
			delete pIBO;

			FT_Done_Face(face);
		}
		void Text::Init()
		{
#if _DEBUG
			// Initialize the freetype library
			if (FT_Init_FreeType(&library) != 0)
				THROW_ERROR("Failed to initialize the FreeType library!");
#else
			FT_Init_FreeType(&library);
#endif

			// Create the font shaders
			const char* vsCode = R"(
				#version 330 core
				
				layout(location = 0) in vec2 position;
				layout(location = 1) in vec2 textCoord;
				layout(location = 2) in float textUnit;
				
				uniform mat4 uModelTranslation;
				uniform mat4 uModelScale;
				uniform mat4 uModelRotation;
				
				uniform mat4 uCameraTranslation;
				uniform mat4 uCameraRotation;
				
				uniform mat4 uProjection;
				
				out vec2 vTextCoord;
				out float vTextUnit;
				
				void main()
				{
					mat4 scale = uModelScale;
					mat4 rotation = uModelRotation * uCameraRotation;
					mat4 translation = uModelTranslation * uCameraTranslation;
				
					gl_Position =  uProjection * translation * rotation * scale * vec4(position.x, position.y, 0.0f, 1.0f);
					vTextCoord = textCoord;
					vTextUnit = textUnit;
				}
			)";

			const char* fsCode = R"(
				#version 330 core
				
				out vec4 uFragColor;
				
				in vec2 vTextCoord;
				in float vTextUnit;
				
				uniform vec4 uColor;
				uniform sampler2D uTextureUnits[32];
				
				void main()
				{
					int textureUnit = int(vTextUnit);
				
					vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(uTextureUnits[textureUnit], vTextCoord).r);
					uFragColor = uColor * sampled;
				}
			)";

			pShader = new Shader(vsCode, fsCode, true);
			pShader->Bind();

			int textureUnits[32];
			for (int i = 0; i < 32; i++)
				textureUnits[i] = i;
			pShader->SetUniform1iv("uTextureUnits", textureUnits, 32);

			pShader->Unbind();

#if _DEBUG
			std::cout << " -> Text Rendering Initialized!" << std::endl;
#endif
		}

		void Text::Free()
		{
			delete pShader;

			FT_Done_FreeType(library);
		}

		void Text::LoadCharacters()
		{
			for (int i = 0; i < 128; i++)
			{
#if _DEBUG
				// Load a character from the font as an 8-bit texture
				if (FT_Load_Char(face, i, FT_LOAD_RENDER) != 0)
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
#else
				FT_Load_Char(face, i, FT_LOAD_RENDER);
#endif

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				// Send texture data to the gpu 
				unsigned int textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				glBindTexture(GL_TEXTURE_2D, 0);

				Character ch = { textureID, face->glyph->bitmap_left, face->glyph->bitmap_top, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->advance.x };
				pCharacters[i] = ch;
			}
		}

		void Text::SetText(const char* string)
		{
			// Clear the buffers with previous text's data
			pVAO->Bind();

			pVBO[POS_BUFFER].Bind();
			pVBO[POS_BUFFER].SendData(sizeof(float) * 8 * 32, 0);

			pVBO[TCOORD_BUFFER].Bind();
			pVBO[TCOORD_BUFFER].SendData(sizeof(float) * 8 * 32, 0);

			pVBO[TINDEX_BUFFER].Bind();
			pVBO[TINDEX_BUFFER].SendData(sizeof(float) * 4 * 32, 0);

			pIBO->Bind();
			pIBO->SendDataIntoRegion(0, sizeof(unsigned short) * 6 * 32, 0);

			memset(pTextureUnits, 0, sizeof(Character) * 32);

			std::string text = string;
			pTextLength = 0;
			pTextSize.x = 0.0f;
			pTextSize.y = 0.0f;

			// First, calculate the total width and the height of the text
			int maxHeight = 0;
			for (char ch : text)
			{
				pTextSize.x += (pCharacters[ch].advance >> 6); // Set the width
				if (pCharacters[ch].height > maxHeight)
					maxHeight = pCharacters[ch].height;
			}
			pTextSize.y = maxHeight; // Set the height

			unsigned int advance = 0;
			unsigned int textureUnit = 1;

			int vertexDataOffset = 0;
			int textIndexDataOffset = 0;
			int indexDataOffset = 0;
			short indexOffset = 0;

			// Create the quads to render text to
			for (char ch : text)
			{
				float xbearing = pCharacters[ch].bearingX;
				float ybearing = pCharacters[ch].bearingY;
				float textureWidth = pCharacters[ch].width;
				float textureHeight = pCharacters[ch].height;

				float totalXOffset = advance + xbearing;
				float totalYOffset = (textureHeight - ybearing);

				maths::vec2 bottomLeft = { -pTextSize.x / 2, -pTextSize.y / 2 };

				float positions[8] =
				{
					bottomLeft.x + totalXOffset,						bottomLeft.y - totalYOffset,
					bottomLeft.x + totalXOffset + textureWidth,			bottomLeft.y - totalYOffset,
					bottomLeft.x + totalXOffset + textureWidth,			bottomLeft.y - totalYOffset + textureHeight,
					bottomLeft.x + totalXOffset,						bottomLeft.y - totalYOffset + textureHeight,
				};

				float textCoords[8] =
				{
					0.0f, 1.0f,
					1.0f, 1.0f,
					1.0f, 0.0f,
					0.0f, 0.0f
				};

				float textUnit[4] =
				{
					(float)textureUnit,
					(float)textureUnit,
					(float)textureUnit,
					(float)textureUnit
				};

				unsigned short indices[6] = { 0 + indexOffset, 1 + indexOffset, 2 + indexOffset, 2 + indexOffset, 3 + indexOffset, 0 + indexOffset };

				pVBO[POS_BUFFER].Bind();
				pVBO[POS_BUFFER].SendDataIntoRegion(vertexDataOffset, sizeof(float) * 8, positions);

				pVBO[TCOORD_BUFFER].Bind();
				pVBO[TCOORD_BUFFER].SendDataIntoRegion(vertexDataOffset, sizeof(float) * 8, textCoords);

				pVBO[TINDEX_BUFFER].Bind();
				pVBO[TINDEX_BUFFER].SendDataIntoRegion(textIndexDataOffset, sizeof(float) * 4, textUnit);

				pIBO->SendDataIntoRegion(indexDataOffset, sizeof(unsigned short) * 6, indices);

				pTextureUnits[textureUnit] = pCharacters[ch];
				textureUnit++;

				advance += (pCharacters[ch].advance >> 6);

				vertexDataOffset += sizeof(float) * 8;
				textIndexDataOffset += sizeof(float) * 4;
				indexDataOffset += sizeof(unsigned short) * 6;
				indexOffset += 4;
				pTextLength++;
			}
			pTextSize.x = pTextSize.x * pScale;
			pTextSize.y = pTextSize.y * pScale;

			pVAO->Unbind();
		}
		void Text::SetPosition(float x, float y)
		{
			pPosition = { x, y };
		}
		void Text::SetScale(float scale)
		{
			pScale = scale;

			pTextSize.x = pTextSize.x * scale;
			pTextSize.y = pTextSize.y * scale;
		}
		void Text::SetRotation(float angle)
		{
			pRotationAngle = angle;
		}
		void Text::SetColor(float r, float g, float b, float a)
		{
			pColor = { r, g, b, a };
		}
		void Text::BindTextures()
		{
			for (int i = 1; i <= pTextLength; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, pTextureUnits[i].textureID);
			}
		}

		void Text::Render()
		{
			BindTextures();
			pVAO->Bind();
			pShader->Bind();

			pTranslation = maths::translate(maths::vec3(pPosition.x + (pTextSize.x / 2) * pScale, pPosition.y - (pTextSize.y / 2) * pScale, 0.0f));
			pScaleMat = maths::scale(maths::vec3(pScale, pScale, 1.0f));
			pRotation = maths::rotate(-TO_RADIANS(pRotationAngle), maths::vec3(0.0f, 0.0f, 1.0f));

			pShader->SetUniformMat4f("uModelScale", pScaleMat);
			pShader->SetUniformMat4f("uModelRotation", pRotation);
			pShader->SetUniformMat4f("uModelTranslation", pTranslation);
			pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
			pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
			pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

			pShader->SetUniformVec4f("uColor", pColor);

			glDrawElements(GL_TRIANGLES, pIBO->GetIndiciesCount(), GL_UNSIGNED_SHORT, 0);

			pVAO->Unbind();
		}
	}
}