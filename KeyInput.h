#pragma once
#include <vector>
#include <map>
#include <GLFW/glfw3.h>

class KeyInput
{
	std::map<int, bool> keymap;
	std::map<int, bool> releasemap;
public:
	KeyInput(std::vector<int> keysToListen, std::vector<int> keysToListenRelease = {});
	~KeyInput();
	void setupKeyCallback(GLFWwindow* window);
	void setKeyDown(int key, bool flag);
	bool getKeyDown(int key);
	bool getMouseButtonDown(int key);
	void setKeyReleased(int key, bool flag);
	bool getKeyReleased(int key);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static std::vector<KeyInput*> _instances;

};

