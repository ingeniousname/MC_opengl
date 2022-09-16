#include "World.h"
#include "Camera.h"
#include "Player.h"
#include <cmath>


// static fields necessary for callback function

Player::Player(glm::vec3 initialPos) : playerInput({ GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT }, { GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT })
{
	position = initialPos;
	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);
	speed = 0.2f;
    height = 1.5f;

}

void Player::update(World& world, glm::vec3 facing, glm::vec3 right, BlockType inHand)
{

    // if i'm not flying - make gravity work
    if (!isFlying)
    {
        acceleration.y = 0;
        if (!isOnGround)
            velocity.y -= 0.25f * speed;
        isOnGround = false;
    }


    // update position, velocity, acceleration vectors
    velocity += acceleration;
    acceleration = { 0, 0, 0 };

    glm::vec3 delta = velocity * speed;
    if (!isFlying)
        collide(world, delta);
    else position += delta;


    // check for any action taking place
	if (playerInput.getKeyDown(GLFW_KEY_W))
		acceleration += facing * 0.15f;
	if (playerInput.getKeyDown(GLFW_KEY_S))
		acceleration -= facing * 0.15f;
	if (playerInput.getKeyDown(GLFW_KEY_A))
		acceleration -= right * 0.15f;
	if (playerInput.getKeyDown(GLFW_KEY_D))
		acceleration += right * 0.15f;
    if (playerInput.getKeyDown(GLFW_KEY_SPACE))
        jump();
    if (playerInput.getMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        destroyBlock(world, facing);
    if (playerInput.getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        placeBlock(world, facing, inHand);

    
    // decelerate
    velocity.x *= 0.75f;
    velocity.z *= 0.75f;
    if(isFlying)
       velocity.y *= 0.75f;
    //std::cout << isOnGround << std::endl;
}

BlockType Player::destroyBlock(World& world, glm::vec3 facing)
{
    // get a vector that indicates where the player is facing
    glm::vec3 facingNormal = facing;
    for (int i = 0; i < 12; i++)
    {
        // shoot a ray to find the nearest block that the player is facing
        auto block = world.getBlock(glm::vec3(position.x, position.y + height, position.z) + facing);
        if (block != AIR_BLOCK)
        {
            world.changeBlock(glm::vec3(position.x, position.y + height, position.z) + facing);
            return block;
        }
        else facing += facingNormal * 0.5f;
    }
    return AIR_BLOCK;
}

void Player::placeBlock(World& world, glm::vec3 facing, BlockType type)
{
    // get a vector that indicates where the player is facing
    glm::vec3 facingNormal = facing;
    for (int i = 0; i < 12; i++)
    {
        // try finding a block to which you can stick your placed block
        auto block = world.getBlock(glm::vec3(position.x, position.y + height, position.z) + facing);
        if (block != AIR_BLOCK)
        {
            while (block != AIR_BLOCK)
            {
                // take a step back, find room for your block
                facing -= facingNormal * 0.05f;
                block = world.getBlock(glm::vec3(position.x, position.y + height, position.z) + facing);
            }
            world.changeBlock(glm::vec3(position.x, position.y + height, position.z) + facing, type);
            break;
        }
        else facing += facingNormal * 0.5f;
    }
}

void Player::jump()
{
    if (isOnGround)
    {
        isOnGround = false;
        velocity.y = 1.0f;
    }
}

void Player::collide(World& world, glm::vec3 delta)
{
    // what the fuck?
    bool xcollision = false, ycollision = false, zcollision = false;
    float y = position.y;
    while(y < position.y + AABB.y + 0.1f)
    {
        float xoffset = delta.x > 0 ? AABB.x : -AABB.x;
        float zoffset = delta.z > 0 ? AABB.z : -AABB.z;
        auto blockx = world.getBlock({ position.x + delta.x + xoffset, y, position.z });
        auto blocky = world.getBlock({ position.x, y + delta.y, position.z });
        auto blockz = world.getBlock({ position.x, y, position.z + delta.z + zoffset});
        if (blockx != AIR_BLOCK)
        {
            /*position.x = int(position.x + delta.x + xoffset) - xoffset;
            if (delta.x < 0)
                position.x += 1;*/
            velocity.x = 0;
            xcollision = true;
        }
        if (blockz != AIR_BLOCK)
        {
            /*position.z = int(position.z + delta.z + zoffset) - zoffset;
            if (delta.z < 0)
                position.z += 1;*/
            velocity.z = 0;
            zcollision = true;
        }

        if (blocky != AIR_BLOCK)
        {
            ycollision = true;
            velocity.y = 0;
            if(delta.y < 0)
                isOnGround = true;
        }
        y += AABB.y;
    }

   

    if (!xcollision) position.x += delta.x;
    if (!zcollision) position.z += delta.z;
    if (!ycollision) position.y += delta.y;

}
