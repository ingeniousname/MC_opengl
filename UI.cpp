#include "UI.h"
#include "Shader/shader.h"
#include "GL/glew.h"

UI::UI()
{
  
}

UI::~UI()
{
	glDeleteVertexArrays(1, &this->cross.VAO);
	glDeleteBuffers(1, &this->cross.IBO);
}

void UI::initCrossData()
{
	float crossData[] = { -0.03f, -0.005f, //horizontal
					  0.03f, -0.005f,
					  0.03f,  0.005f,
					 -0.03f,  0.005f,

					 -0.005f, -0.03f, // vertical
					  0.005f, -0.03f,
					  0.005f,  0.03f,
					 -0.005f,  0.03f };

	unsigned int indicies[] = { 0, 1, 2,
							  2, 3, 0,
							  4, 5, 6,
							  6, 7, 4 };

	// initialize opengl stuff
	this->cross.init(&crossData[0], &indicies[0], 2, 8, 12);
}

RenderInfo& UI::getCrossData()
{
	return this->cross;
}
