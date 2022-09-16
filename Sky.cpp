#include "Sky.h"
#include "GL/glew.h"
#include <iostream>

Sky::Sky()
{
    this->daytime.reset();
}

void Sky::update()
{
    if (daytime.getTime() > 480)
    {
        daytime.reset();
        night = !night;
    }
}

void Sky::initBodyData()
{
    glGenVertexArrays(1, &this->bodyRenderInfo.VAO);
    glBindVertexArray(this->bodyRenderInfo.VAO);

    float verticies[] = {
        -2.f, 0.f, -2.f,
        2.f, 0.f, -2.f,
        2.f, 0.f, 2.f,
        -2.f, 0.f, 2.f

    };

    unsigned indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenBuffers(1, &this->bodyRenderInfo.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bodyRenderInfo.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * 6, indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer);
    this->bodyRenderInfo.numIndicies = 6;


}

glm::vec3 Sky::getCurrentSkyColor()
{
    return skyColor;
}

std::pair<glm::vec3, glm::mat4> Sky::getSunPositionData(glm::vec3 playerPos)
{
    std::pair<glm::vec3, glm::mat4> result;
    float sun_distance = 199.f;
    double time = this->daytime.getTime();
    result.first = {sun_distance * cos(time / 10000 * 2 * 3.1415f / 30), sun_distance * sin(time / 10000 * 2 * 3.1415f / 30), 0.f};

    result.second = glm::mat4(1.f);
    result.second = glm::rotate(result.second, glm::radians(90.f) + (float)atan2(result.first.y, result.first.x), glm::vec3(0.f, 0.f, 1.f));
    result.second = glm::scale(result.second, glm::vec3(2.f, 1.f, 2.f));

    result.first += playerPos;
    return result;
}



RenderInfo& Sky::getSkyDrawData()
{
    return this->bodyRenderInfo;
}
