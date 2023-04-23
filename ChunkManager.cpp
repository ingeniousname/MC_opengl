#include "ChunkManager.h"

void ChunkManager::addChunk(glm::ivec2 chunkCoords)
{
	this->Chunks.insert(std::make_pair(chunkCoords, Chunk(chunkCoords * 16)));
	//this->Chunks[chunkCoords].setBlockData(terrainGenerator.getChunkBlockData(chunkCoords * 16));
	//this->Chunks[chunkCoords].setBlockData(terrainGenerator.getChunkBlockData(chunkCoords * 16));
	this->Chunks[chunkCoords].setBlockData(terrainGenerator.flatTerrain());
}

// chunk coords - allow access to a chunk where given block (at the worldCoords) is located
glm::ivec2 worldToChunkCoords(glm::vec2 worldCoords) 
{
	short xoffset = worldCoords.x < 0 ? -1 : 0;
	short zoffset = worldCoords.y < 0 ? -1 : 0;
	return glm::ivec2(int(worldCoords.x / 16 + xoffset), int(worldCoords.y / 16 + zoffset));
}

Chunk& ChunkManager::getChunk(glm::vec2 coords) 
{
	return Chunks[worldToChunkCoords(coords)];
}

bool ChunkManager::isChunkActive(glm::ivec2 chunkCoords)
{
	return Chunks[chunkCoords].isActive();
}

bool ChunkManager::isChunkLoaded(glm::ivec2 chunkCoords)
{
	return Chunks[chunkCoords].isLoaded();
}

Chunk& ChunkManager::getChunkByChunkCoords(glm::ivec2 chunkCoords)
{
	return Chunks.at(chunkCoords);
}

void ChunkManager::loadChunk(Chunk* chunk, glm::ivec2 chunkCoords)
{
	if (chunk == nullptr) return;
	//std::cout << "Chunk loaded: " << chunkCoords.x << " x " << chunkCoords.y << std::endl;
	// [0] = UP, [1] = RIGHT, [2] = DOWN, [3] = LEFT
	glm::ivec2 directions[4] = { glm::ivec2(0, 1), glm::ivec2(1, 0), glm::ivec2(0, -1), glm::ivec2(-1, 0) };

	std::array<Chunk*, 4> neighbourChunks;
	for (int k = 0; k < 4; k++)
	{
		if (Chunks.find(chunkCoords + directions[k]) == Chunks.end())
			addChunk(chunkCoords + directions[k]);
		neighbourChunks[k] = &getChunkByChunkCoords(chunkCoords + directions[k]);
	}
	chunkMeshGenerator.generateChunkMesh(chunk, neighbourChunks);
	chunk->setLoadedFlag(true);
	chunk->setActiveFlag(true);

}

void ChunkManager::updateAroundPosition(glm::vec2 coords)
{
	if (!chunkLoadQueue.empty()) return;
	for (auto it = Chunks.begin(); it != Chunks.end(); it++)
		it->second.setActiveFlag(false);
	glm::ivec2 chunkCoords = worldToChunkCoords(coords);
	//std::cout << "worldCoords: " << coords.x << " x " << coords.y << ", chunkCoords: " << chunkCoords.x << " x " << chunkCoords.y << std::endl;


	for (int i = -4; i <= 4; i++)
	{
		for (int j = -4; j <= 4; j++)
		{
			// if the chunk is found...
			if (Chunks.find(glm::ivec2(chunkCoords.x + i, chunkCoords.y + j)) != Chunks.end())
			{
				Chunk* currChunk = &getChunkByChunkCoords(glm::ivec2(chunkCoords.x + i, chunkCoords.y + j));
				if (!currChunk->isLoaded())
					chunkLoadQueue.push(std::make_pair(glm::ivec2(chunkCoords.x + i, chunkCoords.y + j), currChunk));
				else currChunk->setActiveFlag(true);
			}
			else this->addChunk(glm::ivec2(chunkCoords.x + i, chunkCoords.y + j)); // add missing chunk
		}
	}
}

std::vector<RenderInfo> ChunkManager::getChunkDrawData()
{
	std::vector<RenderInfo> result;
	//std::cout << "Total chunks: " << Chunks.size() << std::endl;
	for (auto it = Chunks.begin(); it != Chunks.end(); it++)
	{
		if (it->second.isActive())
		{
			result.push_back(it->second.getRenderInfo());
		}
	}
	return result;
}

std::pair<glm::ivec2, Chunk*> ChunkManager::popChunkQueue()
{
	if (chunkLoadQueue.empty()) return std::pair<glm::ivec2, Chunk*>{{0, 0}, nullptr};
	auto data = chunkLoadQueue.top();
	chunkLoadQueue.pop();
	return data;
}


