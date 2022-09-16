#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(std::string shaderName) : Renderer(shaderName)
{
	shader.setUniform1i("maxTextures", 4);
}

void ChunkRenderer::draw(const RenderInfo& info)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	this->drawfunc(info);
}

void ChunkRenderer::updateProjectionViewMatrix(glm::mat4x4 VP)
{
	// set the "View-Projection" matrix
	this->shader.setUniformMat4fv("VP", VP);
}

void ChunkRenderer::updateSunPosition(glm::vec3 sunPosition)
{
	this->shader.setUniform3f("sunPos", sunPosition);
}
