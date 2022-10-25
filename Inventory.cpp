#include "Inventory.h"
#include "GL/glew.h"


void Inventory::init()
{
	float tileData[] = {
		-1.f, -1.f,
		1.f, -1.f,
		1.f, 1.f,
		-1.f, 1.f,
		-0.75f, -0.75f,
		 0.75f, -0.75f,
		 0.75f,  0.75f,
		-0.75f,  0.75f,

	};

	unsigned int tileIndicies[] = {
		0, 1, 5,
		5, 4, 0,
		1, 2, 6,
		6, 5, 1,
		2, 3, 7,
		7, 6, 2,
		3, 7, 4,
		4, 0, 3
	};

	float backgroundData[] = {
		-0.5f, -1.f,
		0.5f, -1.f,
		0.5f, -0.8f,
		-0.5f, -0.8f,

	};

	float cubePreviewData[] = {
		-0.75f, -0.75f, 0.f, 0.f,
		 0.75f, -0.75f, 1.f, 0.f,
		 0.75f,  0.75f, 1.f, 1.f,
		-0.75f,  0.75f, 0.f, 1.f
	};




	unsigned int backgroundIndicies[] = {
		0, 1, 2,
		2, 3, 0
	};




	// create RenderInfo for tiles
	this->tile.init(tileData, tileIndicies, 2, 8, 24);

	// create RenderInfo for background
	this->background.init(backgroundData, backgroundIndicies, 2, 4, 6);

	this->initCubePreview();
}

void Inventory::update()
{
	if (KeyInput::getInstance()->getMouseButtonDown(GLFW_KEY_LEFT))
	{
		if (this->highlighted == 0) this->highlighted = size - 1;
		else this->highlighted = (this->highlighted - 1) % size;
	}
	if (KeyInput::getInstance()->getMouseButtonDown(GLFW_KEY_RIGHT)) this->highlighted = (this->highlighted + 1) % size;
}

void Inventory::initCubePreview()
{
	float cubePreviewData[] = {
		-0.75f, -0.75f, 0.f, 0.f,
		 0.75f, -0.75f, 1.f, 0.f,
		 0.75f,  0.75f, 1.f, 1.f,
		-0.75f,  0.75f, 0.f, 1.f
	};

	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};


	glGenVertexArrays(1, &this->cubePreview.VAO);
	glBindVertexArray(this->cubePreview.VAO);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, cubePreviewData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float) * 2));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &this->cubePreview.IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->cubePreview.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indicies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	glDeleteBuffers(1, &buffer);

	this->cubePreview.numIndicies = 6;









}

void Inventory::updateStorage(BlockType block, int changeValue)
{
	for (int i = 0; i < size; i++)
	{
		if (this->storage[i].block == block)
		{
			if (this->storage[i].count < 64)
				this->storage[i].count += changeValue;
			if (this->storage[i].count == 0)
			{
				this->storage[i].block = AIR_BLOCK;
			}
		}
	}
	if(changeValue > 0)
		for (int i = 0; i < size; i++)
		{
			if (this->storage[i].block == AIR_BLOCK)
			{
				this->storage[i].block = block;
				this->storage[i].count = changeValue;
			}
		}
}

BlockType Inventory::getSelectedBlock()
{
	//return this->storage[this->highlighted].block;
	return BlockType(this->highlighted + 1);
}

void Inventory::draw(UIRenderer* renderer)
{

	renderer->setModelMatrix();
	renderer->setColor(glm::vec3(0.f, 1.f, 1.f));
	renderer->draw(this->background);

	for (int i = 0; i < size; i++)
	{
		renderer->setColor(glm::vec3(1.f, 0.f, 0.f));
		if(i == highlighted) renderer->setColor(glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-0.4f + 0.2f * i, -0.9f, 0.f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.f));
		renderer->setModelMatrix(model);
		renderer->draw(this->tile);
		renderer->drawCubePreview(this->cubePreview, i * 4 / 5);
	}

	renderer->setColor();
	renderer->setModelMatrix();
}
