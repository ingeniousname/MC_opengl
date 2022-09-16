#pragma once
#include "Vendor/glm/glm/glm.hpp"
#include "KeyInput.h"

class World;

class Player
{
	glm::vec3 position, velocity, acceleration, AABB{0.3f, 1.7f, 0.3f};
	float speed, height;
	KeyInput playerInput;
	bool isOnGround = false, isFlying = false;

	void collide(World& world, glm::vec3 delta);
	void jump();
	BlockType destroyBlock(World& world, glm::vec3 facing);
	void placeBlock(World& world, glm::vec3 facing, BlockType type);
public:
	Player(glm::vec3 initialPos);

	void setKeyCallback(GLFWwindow* window) { playerInput.setupKeyCallback(window); };
	void update(World& world, glm::vec3 facing, glm::vec3 right, BlockType inHand);

	glm::vec3 getPosition() { return position; };
	float getPlayerHeight() { return height; };
};



