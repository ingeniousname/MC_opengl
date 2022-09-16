#pragma once
#include "Renderer/Renderer.h"
class ChunkRenderer : public Renderer
{
public:
	ChunkRenderer(std::string shaderName);
	virtual void draw(const RenderInfo& info);
	void updateProjectionViewMatrix(glm::mat4x4 VP);
	void updateSunPosition(glm::vec3 sunPosition);
};

