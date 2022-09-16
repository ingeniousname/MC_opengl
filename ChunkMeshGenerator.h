#pragma once
#include "Chunk.h"


class ChunkMeshGenerator
{
public:
	void generateChunkMesh(Chunk* chunk, const std::array<Chunk*, 4>& neighbourChunks);
	void tryAddFaceToMesh(Chunk* chunk, const std::array<Chunk*, 4>& neighbourChunks,
		std::vector<float>& data, std::vector<unsigned int>& indicies, unsigned int& num_verticies, 
		Face face, BlockType type, int xpos, int ypos, int zpos);
};

