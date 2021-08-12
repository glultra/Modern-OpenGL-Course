#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	// Ambient
	float ambientStrength = 0.7f;
	vec3 ambient = ambientStrength * lightColor;


	// Result of lights
	vec3 result = (ambient) * objectColor; 
	FragColor = vec4(result,1.0f);
}