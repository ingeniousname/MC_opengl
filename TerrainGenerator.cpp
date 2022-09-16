#include "TerrainGenerator.h"

std::array<std::array<std::vector<BlockType>, 16>, 16> TerrainGenerator::getChunkBlockData(glm::ivec2 chunkPos)
{
	std::array<std::array<std::vector<BlockType>, 16>, 16> sampleBlockData;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			//use perlin noise (only for height generation)
			float value = glm::perlin(glm::vec2(float(chunkPos.x + i), float(chunkPos.y + j)) / 20.0f);
			value = (value + 1) / 2;
			value *= 16;
			for (int k = 0; k < value; k++)
				sampleBlockData[i][j].push_back(BlockType(STONE_BLOCK));

			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(GRASS_BLOCK));
		}

	return sampleBlockData;
}

std::array<std::array<std::vector<BlockType>, 16>, 16> TerrainGenerator::flatTerrain()
{
	std::array<std::array<std::vector<BlockType>, 16>, 16> sampleBlockData;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 7; k++)
				sampleBlockData[i][j].push_back(BlockType(STONE_BLOCK));

			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(DIRT_BLOCK));
			sampleBlockData[i][j].push_back(BlockType(GRASS_BLOCK));
		}
	return sampleBlockData;
}
