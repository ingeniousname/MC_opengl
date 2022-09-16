#include "SkyRenderer.h"

SkyRenderer::SkyRenderer(std::string shaderName) : Renderer(shaderName)
{

}

void SkyRenderer::draw(const RenderInfo& info)
{
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	this->drawfunc(info);
}

void SkyRenderer::setSunShader(const glm::vec3& sun_position, const glm::mat4& model)
{
	this->shader.setUniform3f("SunPosition", sun_position);
	this->shader.setUniformMat4fv("model", model);

}

void SkyRenderer::updateProjectionViewMatrix(glm::mat4x4 VP)
{
	// set the "View-Projection" matrix
	this->shader.setUniformMat4fv("VP", VP);
}
