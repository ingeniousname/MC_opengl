#pragma once
#include <unordered_map>
#include "ChunkManager.h"
#include "ChunkRenderer.h"

class World
{
	ChunkManager chunkManager;
public:
	World();
	void update(glm::vec2 worldCoords);
	void drawChunks(ChunkRenderer& renderer);
	BlockType getBlock(glm::vec3 worldCoords);
	void changeBlock(glm::vec3 worldCoords, BlockType type = AIR_BLOCK);
};

