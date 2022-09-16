#pragma once
#include "Clock/Clock.h"
#include "Vendor/glm/glm/gtx/transform.hpp"
#include "Vendor/glm/glm/gtc/matrix_transform.hpp"
#include <vector>
#include "RenderInfo.h"

class Sky
{
	Clock daytime;
	glm::vec3 skyColor;
	bool night = false;
	RenderInfo bodyRenderInfo;
public:
	Sky();
	void update();
	void initBodyData();
	glm::vec3 getCurrentSkyColor();
	std::pair<glm::vec3, glm::mat4> getSunPositionData(glm::vec3 playerPos);
	RenderInfo& getSkyDrawData();
};

