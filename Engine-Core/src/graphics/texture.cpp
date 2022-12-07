#include "texture.h"
#include <externals/stb_image/stb_image.h>

#include "util/error_handling.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ds {
	namespace graphics {
		Texture::Texture(const char* filePath)
			:pTextureID(0), pTexturePath(filePath), pPixelBuffer(nullptr), pWidth(0), pHeight(0), pChannels(0)
		{
			stbi_set_flip_vertically_on_load(1);
			pPixelBuffer = stbi_load(filePath, &pWidth, &pHeight, &pChannels, 4);
#if _DEBUG
			if (pPixelBuffer == nullptr)
				THROW_ERROR("STBI_IMAGE ERROR: Failed to load texture!");
#else
			void;
#endif

			glGenTextures(1, &pTextureID);
			glBindTexture(GL_TEXTURE_2D, pTextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixelBuffer);

			if (pPixelBuffer)
				stbi_image_free(pPixelBuffer);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Texture::Texture(unsigned int width, unsigned int height, unsigned char* pixelData)
			:pTextureID(0), pTexturePath(""), pPixelBuffer(nullptr), pWidth(width), pHeight(height), pChannels(0)
		{
			glGenTextures(1, &pTextureID);
			glBindTexture(GL_TEXTURE_2D, pTextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Texture::~Texture()
		{
			glDeleteTextures(1, &pTextureID);
		}

		void Texture::Bind(unsigned int slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, pTextureID);

			glActiveTexture(GL_TEXTURE0);
		}

		void Texture::Unbind(unsigned int slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}