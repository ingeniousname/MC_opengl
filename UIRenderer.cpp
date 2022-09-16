#include "UIRenderer.h"

UIRenderer::UIRenderer(std::string shaderName) : Renderer(shaderName)
{
	cubePreviewShader.createFromFile("CubePreview");
}

void UIRenderer::draw(const RenderInfo& info)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	this->drawfunc(info);
}

void UIRenderer::drawCubePreview(const RenderInfo& info, int cubeIndex)
{
	this->cubePreviewShader.bind();
	this->cubePreviewShader.setUniform1i("cubeIndex", cubeIndex);
	Call(glBindVertexArray(info.VAO));
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.IBO));
	Call(glDrawElements(GL_TRIANGLES, info.numIndicies, GL_UNSIGNED_INT, nullptr)); // OK
}

void UIRenderer::setModelMatrix(glm::mat4 model)
{
	this->shader.setUniformMat4fv("model", model);
	this->cubePreviewShader.setUniformMat4fv("model", model);
}

void UIRenderer::setColor(glm::vec3 color)
{
	this->shader.setUniform3f("color", color);
}
