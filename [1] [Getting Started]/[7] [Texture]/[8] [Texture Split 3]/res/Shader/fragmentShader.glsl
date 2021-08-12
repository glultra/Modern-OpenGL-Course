#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoords * -10.0f) * vec4(colors * ourColor, 1.0f);
}