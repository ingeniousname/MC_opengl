#pragma once
#include "RenderMaster.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "UI.h"
#include "Sky.h"
#include "Inventory.h"
#include <memory>



class App
{
	Inventory inventory;
	GLFWwindow* window;
	Camera camera;
	World world;
	UI ui;
	Player player;
	RenderMaster render_master;
	Sky sky;
	bool closed = false;
	void update();
	void draw();
public:
	App(int width, int height);
	~App();
	void run();
};

