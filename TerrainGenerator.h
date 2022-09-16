#pragma once
#include <vector>
#include <array>
#include <ctime>
#include <cstdlib>
#include "BlockType.h"
#include "Vendor/glm/glm/glm.hpp"
#include "Vendor/glm/glm/gtx/transform.hpp"
#include "Vendor/glm/glm/gtc/noise.hpp"

class TerrainGenerator
{
public:
	TerrainGenerator() {srand(time(NULL)); };
	std::array<std::array<std::vector<BlockType>, 16>, 16> getChunkBlockData(glm::ivec2 chunkPos);
	std::array<std::array<std::vector<BlockType>, 16>, 16> flatTerrain();
};

