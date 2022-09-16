#version 330 core

in vec2 processedTexCoords;

out vec4 out_color;

uniform sampler2D TextureSampler;




void main()
{
	out_color = texture(TextureSampler, processedTexCoords);
}