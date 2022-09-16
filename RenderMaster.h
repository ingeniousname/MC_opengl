#pragma once
#include "SkyRenderer.h"
#include "ChunkRenderer.h"
#include "UIRenderer.h"

class RenderMaster
{
	SkyRenderer* sky_renderer;
	ChunkRenderer* chunk_renderer;
	UIRenderer* ui_renderer;
public:
	RenderMaster() {};
	~RenderMaster();
	void init();
	SkyRenderer* getSkyRenderer();
	ChunkRenderer* getChunkRenderer();
	UIRenderer* getUIRenderer();

};

