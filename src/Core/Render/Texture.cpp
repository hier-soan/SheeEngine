#include "seafx.h"
#include "Texture.h"

namespace SheeEngine
{
	Texture::Texture(const char* texturePath)
	{
		// generate and bind texture
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		// set wrap type
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// set zoom filter type
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// load picture and convey data to texture which has generated
		unsigned char* textureData = stbi_load(texturePath, &m_Width, &m_Height, &m_NrChannel, 0);
		if (textureData)
		{
			GLenum format = 0;
			if (m_NrChannel == 1)
				format = GL_RED;
			else if (m_NrChannel == 3)
				format = GL_RGB;
			else if (m_NrChannel == 4)
				format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::Fail to load texture" << std::endl;
		}

		// free picture data
		stbi_image_free(textureData);
	}

	void Texture::imageFlipVertical(bool value)
	{
		stbi_set_flip_vertically_on_load(value);
	}

	void Texture::SetTexture2DUnit(TextureUnit unit, unsigned int ID)
	{
		glActiveTexture((GLenum)unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::SetTexture3DUnit(TextureUnit unit, unsigned int ID)
	{
		glActiveTexture((GLenum)unit);
		glBindTexture(GL_TEXTURE_3D, ID);
	}
}