#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 model;
uniform int cubeIndex;

out vec2 processedTexCoords;

const int numTextures = 4;



void main()
{
	gl_Position = model * vec4(position, 1.f, 1.f);
	processedTexCoords = vec2(1.0f /float(numTextures) * texCoords.x + cubeIndex / float(numTextures), texCoords.y);

	
}


