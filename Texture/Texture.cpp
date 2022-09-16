#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

Texture::Texture()
{
	glGenTextures(1, &textureBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureBuffer);
}

void Texture::createTextureFromFile(const std::string& name)
{
	stbi_set_flip_vertically_on_load(true);
	type = GL_TEXTURE_2D;
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int numChannels;
	unsigned char* data = stbi_load((name + ".png").data(), &this->width, &this->height, &numChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "failed to load texture: " << name << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::createCubemapFromFiles(const std::string& name)
{
	type = GL_TEXTURE_CUBE_MAP;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureBuffer);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (unsigned int i = 0; i < 6; i++)
	{
		int numChannels;
		// 0 - right, 1 - left, 2 - top, 3 - bottom, 4 - back, 5 - front
		unsigned char* data = stbi_load((name + char(48 + i) + ".png").data(), &this->width, &this->height, &numChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else std::cout << "failed to load texture: " << name << std::endl;
		stbi_image_free(data);
	}
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}



void Texture::createCubemapFromFile(const std::string& name)
{
	type = GL_TEXTURE_CUBE_MAP;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureBuffer);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int numChannels;
	// 0 - right, 1 - left, 2 - top, 3 - bottom, 4 - back, 5 - front
	unsigned char* data = stbi_load((name + ".png").data(), &this->width, &this->height, &numChannels, 0);

	for (unsigned int i = 0; i < 6; i++)
	{
		if (data)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else std::cout << "failed to load texture: " << name << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture::bind() const
{
	glBindTexture(type, textureBuffer);
}


