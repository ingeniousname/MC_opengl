#pragma once
#include "GL/glew.h"

struct RenderInfo
{
	unsigned int VAO; // Vertex Array Object
	unsigned int IBO; // Index Buffer Object
	unsigned int numIndicies;

	RenderInfo() : VAO(0), IBO(0), numIndicies(0) {};
	RenderInfo(unsigned int _VAO, unsigned int _IBO, unsigned int _numIndicies) : VAO(_VAO), IBO(_IBO), numIndicies(_numIndicies) {};

	void init(float* data, unsigned* indicies, unsigned vectorSize, unsigned numVerticies, unsigned numIndicies)
	{
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
	
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerticies * vectorSize, data, GL_STATIC_DRAW);
	
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, vectorSize, GL_FLOAT, GL_FALSE, 0, (const void*)0);
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndicies, indicies, GL_STATIC_DRAW);
		this->numIndicies = numIndicies;
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	
		glDeleteBuffers(1, &buffer);
	}
};