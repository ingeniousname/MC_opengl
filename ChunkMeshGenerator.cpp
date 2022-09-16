#include "ChunkMeshGenerator.h"

void ChunkMeshGenerator::generateChunkMesh(Chunk* chunk, const std::array<Chunk*, 4>& neighbourChunks)
{
	glGenVertexArrays(1, &chunk->info.VAO);

	unsigned int num_verticies = 0;
	unsigned int buffer;
	std::vector<float> data;
	std::vector<unsigned int> indicies;

	// for each block and each face of this block - see if it is necessary to draw it
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			for (int k = 0; k < chunk->blockData[i][j].size(); k++)
				for (int l = 0; l < 6; l++)
				{
					this->tryAddFaceToMesh(chunk, neighbourChunks, data, indicies, num_verticies, Face(l), chunk->blockData[i][j][k], i, k, j);
				}



	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBindVertexArray(chunk->info.VAO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(sizeof(float) * 8));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &chunk->info.IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->info.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
	chunk->info.numIndicies = indicies.size();

	glDeleteBuffers(1, &buffer);

}

void ChunkMeshGenerator::tryAddFaceToMesh(Chunk* chunk, const std::array<Chunk*, 4>& neighbourChunks,
	std::vector<float>& data, std::vector<unsigned int>& indicies, unsigned int& num_verticies, 
	Face face, BlockType type, int xpos, int ypos, int zpos)
{
	if (type == AIR_BLOCK) return;

	switch (face)
	{
	case Face::TOP:
	{
		if (ypos < (chunk->blockData[xpos][zpos].size() - 1) && chunk->blockData[xpos][zpos][ypos + 1] != BlockType(0))
			return;
		break;
	}
	case Face::BOTTOM:
	{
		if (ypos > 0 && chunk->blockData[xpos][zpos][ypos - 1] != BlockType(0))
			return;
		break;
	}
	case Face::LEFT:
	{
		if (xpos > 0 && chunk->blockData[xpos - 1][zpos].size() > ypos && chunk->blockData[xpos - 1][zpos][ypos] != BlockType(0))
			return;
		if (xpos == 0 && neighbourChunks[3]->blockData[15][zpos].size() > ypos && neighbourChunks[3]->blockData[15][zpos][ypos] != BlockType(0)) return;
		break;
	}
	case Face::RIGHT:
	{
		if (xpos < 15 && chunk->blockData[xpos + 1][zpos].size() > ypos && chunk->blockData[xpos + 1][zpos][ypos] != BlockType(0))
			return;
		if (xpos == 15 && neighbourChunks[1]->blockData[0][zpos].size() > ypos && neighbourChunks[1]->blockData[0][zpos][ypos] != BlockType(0)) return;
		break;
	}
	case Face::FRONT:
	{
		if (zpos > 0 && chunk->blockData[xpos][zpos - 1].size() > ypos && chunk->blockData[xpos][zpos - 1][ypos] != BlockType(0)) return;
		if (zpos == 0 && neighbourChunks[2]->blockData[xpos][15].size() > ypos && neighbourChunks[2]->blockData[xpos][15][ypos] != BlockType(0)) return;
		break;
	}
	case Face::BACK:
	{
		if (zpos < 15 && chunk->blockData[xpos][zpos + 1].size() > ypos && chunk->blockData[xpos][zpos + 1][ypos] != BlockType(0)) return;
		if (zpos == 15 && neighbourChunks[0]->blockData[xpos][0].size() > ypos && neighbourChunks[0]->blockData[xpos][0][ypos] != BlockType(0)) return;
		break;
	}
	}

	auto blockData = BlockDatabase::get().getFaceData(face);
	glm::vec3 normal;
	switch (face)
	{
		case Face::TOP: normal = { 0.f, 1.f, 0.f }; break;
		case Face::BOTTOM: normal = { 0.f, -1.f, 0.f }; break;
		case Face::LEFT: normal = { -1.f, 0.f, 0.f }; break;
		case Face::RIGHT: normal = { 1.f, 0.f, 0.f }; break;
		case Face::FRONT: normal = { 0.f, 0.f, -1.f }; break;
		case Face::BACK: normal = { 0.f, 0.f, 1.f }; break;
	}


	for (int i = 0; i < 4; i++)
	{
		data.push_back(blockData[5 * i] + xpos + chunk->position.x);
		data.push_back(blockData[5 * i + 1] + ypos);
		data.push_back(blockData[5 * i + 2] + zpos + chunk->position.y);
		data.push_back(blockData[5 * i + 3]);
		data.push_back(blockData[5 * i + 4]);
		data.push_back(normal.x);
		data.push_back(normal.y);
		data.push_back(normal.z);




		data.push_back(BlockDatabase::get().get_texture(type, face));
	}

	indicies.push_back(0 + num_verticies);
	indicies.push_back(1 + num_verticies);
	indicies.push_back(2 + num_verticies);
	indicies.push_back(2 + num_verticies);
	indicies.push_back(3 + num_verticies);
	indicies.push_back(0 + num_verticies);

	num_verticies += 4;
}


