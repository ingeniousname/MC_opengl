#include "Chunk.h"
#include "Clock/Clock.h"


Chunk::Chunk(glm::vec2 _position) : position(_position)
{
	m_isActive = false;
	m_isMeshLoaded = false;
	m_isDataLoaded = false;
}

void Chunk::setBlockData(std::array<std::array<std::vector<BlockType>, 16>, 16> generatedBlockData)
{
	this->blockData = generatedBlockData;
	this->m_isDataLoaded = true;
}

RenderInfo& Chunk::getRenderInfo()
{
	return this->info;
}

BlockType Chunk::getBlock(glm::vec3 worldCoords)
{
	glm::ivec3 localBlockCoords = getLocalChunkCoords(worldCoords);
	if(this->blockData[localBlockCoords.x][localBlockCoords.z].size() <= localBlockCoords.y)
		return AIR_BLOCK;
	else return this->blockData[localBlockCoords.x][localBlockCoords.z][localBlockCoords.y];
	
}

void Chunk::freeRenderInfo()
{
	glDeleteVertexArrays(1, &this->info.VAO);
	glDeleteBuffers(1, &this->info.IBO);
	this->info.numIndicies = 0;
}


std::vector<glm::ivec2> Chunk::changeBlock(glm::vec3 worldCoords, BlockType newBlock)
{
	std::vector<glm::ivec2> neighbours;
	glm::ivec3 localBlockCoords = getLocalChunkCoords(worldCoords);
	if(newBlock == AIR_BLOCK)
		this->blockData[localBlockCoords.x][localBlockCoords.z][localBlockCoords.y] = newBlock;
	else
	{
		while(this->blockData[localBlockCoords.x][localBlockCoords.z].size() <= localBlockCoords.y)
			this->blockData[localBlockCoords.x][localBlockCoords.z].push_back(AIR_BLOCK);
		this->blockData[localBlockCoords.x][localBlockCoords.z][localBlockCoords.y] = newBlock;
	}

	glm::ivec2 directions[4] = { glm::ivec2(0, 1), glm::ivec2(1, 0), glm::ivec2(0, -1), glm::ivec2(-1, 0) };

	if (localBlockCoords.x == 0)
		neighbours.push_back(directions[3]);
	else if(localBlockCoords.x == 15)
		neighbours.push_back(directions[1]);

	if (localBlockCoords.z == 0)
		neighbours.push_back(directions[2]);
	else if (localBlockCoords.z == 15)
		neighbours.push_back(directions[0]);

	return neighbours;
}

// local chunk coords - block coordinates within a chunk
glm::ivec3 getLocalChunkCoords(glm::vec3 worldCoords)
{
	glm::ivec3 localBlockCoords = glm::ivec3(int(worldCoords.x) % 16, int(worldCoords.y), int(worldCoords.z) % 16);
	if (worldCoords.x < 0) localBlockCoords.x = 15 + localBlockCoords.x;
	if (worldCoords.z < 0) localBlockCoords.z = 15 + localBlockCoords.z;
	return localBlockCoords;
}
