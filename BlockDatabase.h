#pragma once
#include <array>
#include <memory>
#include <map>
#include "texture/texture.h"
#include "BlockType.h"


const int BLOCK_COUNT = 4;


enum class Face { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };


class BlockDatabase
{
	std::unique_ptr<Texture> TextureAtlas;
	std::array<std::array<float, 20>, 6> blockFaceData;
public:
	BlockDatabase();
	BlockDatabase(const BlockDatabase& other) = delete;
	BlockDatabase&operator=(const BlockDatabase& other) = delete;
	static BlockDatabase& get();
	unsigned int get_texture(BlockType type, Face face);
	std::array<float, 20> getFaceData(Face face);

};

