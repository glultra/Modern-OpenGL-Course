#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;

void main()
{
	FragColor = vec4(colors * ourColor ,1.0f);
}