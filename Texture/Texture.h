#pragma once
#include "GL/glew.h"
#include <string>
#include <iostream>


// handles both textues and cubemaps
class Texture
{
	unsigned int textureBuffer, type;
	int width, height;
public:
	Texture();
	~Texture();
	void createTextureFromFile(const std::string& filename);
	void createCubemapFromFiles(const std::string& filename);
	void createCubemapFromFile(const std::string& filename);
	void bind() const;
};

