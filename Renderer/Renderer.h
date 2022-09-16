#pragma once
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "BlockDatabase.h"
#include "RenderInfo.h"


class Renderer
{
protected:
	Shader shader;
	void drawfunc(const RenderInfo& info);
public:
	Renderer(std::string shaderName);
	~Renderer();
	virtual void draw(const RenderInfo& info) = 0;
};

