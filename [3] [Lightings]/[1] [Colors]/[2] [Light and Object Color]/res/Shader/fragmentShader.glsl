#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	vec3 result = lightColor * objectColor;
	FragColor = vec4(result,1.0f);
}