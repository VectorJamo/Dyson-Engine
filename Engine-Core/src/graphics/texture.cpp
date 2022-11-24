#include "texture.h"
#include <externals/stb_image/stb_image.h>

namespace ds {
	namespace graphics {
		Texture::Texture(const std::string& filePath)
			:pTextureID(0), pTexturePath(filePath), pPixelBuffer(nullptr), pWidth(0), pHeight(0), pChannels(0)
		{
			stbi_set_flip_vertically_on_load(1);
			pPixelBuffer = stbi_load(filePath.c_str(), &pWidth, &pHeight, &pChannels, 4);

			if (pPixelBuffer == nullptr)
				std::cout << "STBI_IMAGE ERROR: Failed to load texture!" << std::endl;

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