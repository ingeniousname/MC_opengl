#pragma once

#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>
#include "Chunk.h"
#include "ChunkMeshGenerator.h"
#include "TerrainGenerator.h"

class ivec2Hash
{
public:
	std::size_t operator()(const glm::ivec2& vector) const
	{
		return std::hash<int>{}(vector.x) ^ (std::hash<int>{}(vector.y) << 1);
	}
};

class ivec2Compare
{
public:
	bool operator()(const std::pair<glm::ivec2, Chunk*>& v1, std::pair<glm::ivec2, Chunk*>& v2)
	{
		return v1.first.x * v1.first.x + v1.first.y * v1.first.y > v2.first.x * v2.first.x + v2.first.y * v2.first.y;
	}
};





class ChunkManager
{
	std::unordered_map<glm::ivec2, Chunk, ivec2Hash> Chunks;
	std::priority_queue<std::pair<glm::ivec2, Chunk*>, std::vector<std::pair<glm::ivec2, Chunk*>>, ivec2Compare> chunkLoadQueue;
	ChunkMeshGenerator chunkMeshGenerator;
	TerrainGenerator terrainGenerator;
public:
	ChunkManager() {};
	Chunk& getChunk(glm::vec2 coords);
	void updateAroundPosition(glm::vec2 coords);
	std::vector<RenderInfo> getChunkDrawData();
	std::pair<glm::ivec2, Chunk*> popChunkQueue();
	void loadChunk(Chunk* chunk, glm::ivec2 chunkCoords);
	Chunk& getChunkByChunkCoords(glm::ivec2 coords);
private:
	void addChunk(glm::ivec2 chunkCoords);
	bool isChunkActive(glm::ivec2 coords);
	bool isChunkLoaded(glm::ivec2 coords);
};

glm::ivec2 worldToChunkCoords(glm::vec2 worldCoords);