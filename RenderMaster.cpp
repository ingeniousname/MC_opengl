#include "RenderMaster.h"

RenderMaster::~RenderMaster()
{
	delete sky_renderer;
	delete ui_renderer;
	delete chunk_renderer;
}

void RenderMaster::init()
{
	this->sky_renderer = new SkyRenderer("sky");
	this->chunk_renderer = new ChunkRenderer("chunk");
	this->ui_renderer = new UIRenderer("UI");
}

SkyRenderer* RenderMaster::getSkyRenderer()
{
	return this->sky_renderer;
}

ChunkRenderer* RenderMaster::getChunkRenderer()
{
	return this->chunk_renderer;
}

UIRenderer* RenderMaster::getUIRenderer()
{
	return this->ui_renderer;
}
