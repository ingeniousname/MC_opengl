#pragma once
#include "RenderInfo.h"

class UI
{
	RenderInfo cross;
public:
	UI();
	~UI();
	void initCrossData();
	RenderInfo& getCrossData();
};

