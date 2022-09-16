#include "World.h"


World::World()
{
	
}

void World::update(glm::vec2 worldCoords)
{
	chunkManager.updateAroundPosition(worldCoords);
	auto chunkLoadData = chunkManager.popChunkQueue();
	chunkManager.loadChunk(chunkLoadData.second, chunkLoadData.first);
}

void World::drawChunks(ChunkRenderer& renderer)
{
	auto chunkDrawData = chunkManager.getChunkDrawData();
	for (RenderInfo& chunkData : chunkDrawData)
		renderer.draw(chunkData);
}

BlockType World::getBlock(glm::vec3 worldCoords)
{
	return chunkManager.getChunk(glm::vec2(worldCoords.x, worldCoords.z)).getBlock(worldCoords);
}

void World::changeBlock(glm::vec3 worldCoords, BlockType type)
{
	Chunk* chunk = &chunkManager.getChunk(glm::vec2(worldCoords.x, worldCoords.z));
	auto neighboursPosition = chunk->changeBlock(worldCoords, type);
	auto changedChunkCoords = worldToChunkCoords(glm::vec2(worldCoords.x, worldCoords.z));
	chunk->freeRenderInfo();
	chunkManager.loadChunk(chunk, changedChunkCoords);

	for (glm::ivec2 dir : neighboursPosition)
	{
		chunk = &chunkManager.getChunkByChunkCoords(changedChunkCoords + dir);
		chunk->freeRenderInfo();
		chunkManager.loadChunk(chunk, changedChunkCoords + dir);
	}
}

