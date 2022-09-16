#include "BlockDatabase.h"


BlockDatabase::BlockDatabase()
{
 
    TextureAtlas = std::make_unique<Texture>();
    TextureAtlas.get()->createTextureFromFile("TextureAtlas");
    glActiveTexture(GL_TEXTURE0);
    TextureAtlas.get()->bind();

    blockFaceData[int(Face::TOP)] = std::array<float, 20>{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
    blockFaceData[int(Face::BOTTOM)] = std::array<float, 20>{ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    blockFaceData[int(Face::LEFT)] = std::array<float, 20>{ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
    blockFaceData[int(Face::RIGHT)] = std::array<float, 20>{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    blockFaceData[int(Face::FRONT)] = std::array<float, 20>{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    blockFaceData[int(Face::BACK)] = std::array<float, 20>{ 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
}

BlockDatabase& BlockDatabase::get()                        
{
    static BlockDatabase b;
    return b;
}

unsigned int BlockDatabase::get_texture(BlockType type, Face face)
{
    switch (type)
    {
    case BlockType(DIRT_BLOCK): return 0; break;
    case BlockType(GRASS_BLOCK): 
    {
        switch (face)
        {
        case Face::BACK: return 1; break;
        case Face::FRONT: return 1; break;
        case Face::BOTTOM: return 0; break;
        case Face::TOP: return 2; break;
        case Face::LEFT: return 1; break;
        case Face::RIGHT: return 1; break;
        }
        break;
    }
    case BlockType(STONE_BLOCK): return 3; break;
    }
    return 0;
}

std::array<float, 20> BlockDatabase::getFaceData(Face face)
{
    return blockFaceData[int(face)];
}
