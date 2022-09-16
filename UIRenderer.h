#pragma once
#include "Renderer/Renderer.h"
class UIRenderer : public Renderer
{
	Shader cubePreviewShader;
public:
	UIRenderer(std::string shaderName);
	virtual void draw(const RenderInfo& info);
	void drawCubePreview(const RenderInfo& info, int cubeIndex);
	void setModelMatrix(glm::mat4 model = glm::mat4(1.f));
	void setColor(glm::vec3 color = { 1.f, 1.f, 1.f });

};

