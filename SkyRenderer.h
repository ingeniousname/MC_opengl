#pragma once
#include "Renderer/Renderer.h"
class SkyRenderer : public Renderer
{
public:
	SkyRenderer(std::string shaderName);
	virtual void draw(const RenderInfo& info);
	void setSunShader(const glm::vec3& sun_position, const glm::mat4& model);
	void updateProjectionViewMatrix(glm::mat4x4 VP);

};

