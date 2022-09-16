#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureXY;
layout(location = 2) in vec3 normal;
layout(location = 3) in float textureNum;

uniform mat4 VP;
uniform int maxTextures;

out vec2 processedTexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = VP * vec4(position, 1.0f); 
	processedTexCoords = vec2(1.0f /float(maxTextures) * textureXY.x + textureNum / float(maxTextures), textureXY.y);
	Normal = normal;
	FragPos = position;
}