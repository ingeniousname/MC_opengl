#include "App.h"
#include "Clock/Clock.h"

App::App(int width, int height) : camera(width, height), app_input({ GLFW_KEY_ESCAPE }), player(glm::vec3(0.0f, 45.0f, 0.0f))
{

	// glfw setup
	if (!glfwInit())
		std::cout << "error initializing glfw" << std::endl;
	window = glfwCreateWindow(width, height, "my window", NULL, NULL);
	if (!window)
		std::cout << "error with the window creation" << std::endl;

		
	Call(glfwMakeContextCurrent(window));

	// disable cursor
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// callback setup
	glfwSetCursorPosCallback(this->window, Camera::mouse_callback);
	glfwSetWindowSizeCallback(this->window, Camera::window_size_callback);



	//glew setup
	GLenum status = glewInit();
	if (status != GLEW_OK)
		std::cout << "error initializing glew" << std::endl;


	// 3D and texture setup
	Call(glEnable(GL_TEXTURE_2D));
	Call(glEnable(GL_DEPTH_TEST));
	Call(glEnable(GL_CULL_FACE));
	Call(glCullFace(GL_BACK));
	Call(glFrontFace(GL_CW));


	// key classes setup
	//glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f)
	render_master.init();

	app_input.setupKeyCallback(this->window);
	player.setKeyCallback(this->window);
	ui.initCrossData();
	sky.initBodyData();
	inventory.init();
}

App::~App()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::run()
{
	while (!glfwWindowShouldClose(this->window) && !app_input.getKeyDown(GLFW_KEY_ESCAPE))
	{
		this->update();
		this->draw();
	}
}

void App::update()
{
	// what does update world mean? update player mean?

	camera.updateVectors();
	inventory.update();


	render_master.getChunkRenderer()->updateProjectionViewMatrix(camera.getProjectionViewMatrix(player.getPosition(), player.getPlayerHeight()));
	render_master.getSkyRenderer()->updateProjectionViewMatrix(camera.getProjectionViewMatrix(player.getPosition(), player.getPlayerHeight()));

	auto sunPositionData = sky.getSunPositionData(player.getPosition());
	render_master.getChunkRenderer()->updateSunPosition(sunPositionData.first);
	render_master.getSkyRenderer()->setSunShader(sunPositionData.first, sunPositionData.second);
	world.update(glm::vec2(player.getPosition().x, player.getPosition().z));
	player.update(world, camera.getCameraFrontVector(), camera.getCameraRightVector(), inventory.getSelectedBlock());
}

void App::draw()
{
	glClearColor(0.42f, 0.725f, 0.941f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//draw world
	world.drawChunks(*render_master.getChunkRenderer());

	//draw white cross
	render_master.getSkyRenderer()->draw(sky.getSkyDrawData());



	render_master.getUIRenderer()->draw(ui.getCrossData());
	inventory.draw(render_master.getUIRenderer());


	glfwSwapBuffers(window);
	glfwPollEvents();
}
