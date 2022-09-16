#pragma once
#include "Vendor/glm/glm/glm.hpp"
#include <vector>
#include <array>
#include "BlockDatabase.h"
#include "RenderInfo.h"




class Chunk
{
	friend class ChunkMeshGenerator;
	glm::vec2 position;
	std::array<std::array<std::vector<BlockType>, 16>, 16> blockData;
	bool m_isActive, m_isMeshLoaded, m_isDataLoaded;
	RenderInfo info;
public:
	Chunk() : m_isActive(false), m_isMeshLoaded(false), m_isDataLoaded(false) {};
	Chunk(glm::vec2 _position);
	void setBlockData(std::array<std::array<std::vector<BlockType>, 16>, 16> generatedBlockData);
	RenderInfo& getRenderInfo();
	BlockType getBlock(glm::vec3 worldCoords);
	bool isActive() { return this->m_isActive; };
	bool isLoaded() { return this->m_isMeshLoaded; };
	glm::vec2 getPosition() { return this->position; };
	void setActiveFlag(bool flag) { this->m_isActive = flag; };
	void setLoadedFlag(bool flag) { this->m_isMeshLoaded = flag; };
	void freeRenderInfo();
	std::vector<glm::ivec2> changeBlock(glm::vec3 worldCoords, BlockType newBlock);

};

glm::ivec3 getLocalChunkCoords(glm::vec3 worldCoords);