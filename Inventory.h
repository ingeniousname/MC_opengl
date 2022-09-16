#pragma once
#include "BlockType.h"
#include "RenderInfo.h"
#include "UIRenderer.h"
#include "KeyInput.h"

const int size = 5;


struct InventoryData
{
	BlockType block;
	int count;
};

class Inventory
{
	InventoryData storage[size];
	int highlighted;
	RenderInfo tile;
	RenderInfo background;
	RenderInfo cubePreview;
	KeyInput InventoryInput;
public:
	Inventory() : InventoryInput({ GLFW_KEY_LEFT, GLFW_KEY_RIGHT },  { GLFW_KEY_LEFT, GLFW_KEY_RIGHT }) {};
	void init();
	void update();
	void initCubePreview();
	void updateStorage(BlockType block, int changeValue);
	BlockType getSelectedBlock();
	void draw(UIRenderer* renderer);


};

