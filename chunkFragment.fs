#version 330 core


in vec2 processedTexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 color;

uniform sampler2D textureSampler;
uniform vec3 sunPos;


void main()
{
	vec3 lightDirection =  normalize(sunPos - FragPos);
	float diff = max(sqrt(2) * dot(Normal, lightDirection), 0.0f);
	color = max(0.1f + diff, 1.0f) * texture(textureSampler, processedTexCoords);
}