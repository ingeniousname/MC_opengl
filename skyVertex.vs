#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 VP;
uniform mat4 model;
uniform vec3 SunPosition;


void main()
{
	vec4 result = model * vec4(position, 1.0f);
	gl_Position = VP * (result + vec4(SunPosition, 1.0f));
}