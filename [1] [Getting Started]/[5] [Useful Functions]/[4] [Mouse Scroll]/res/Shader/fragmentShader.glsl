#version 330 core

out vec4 FragColor;

in vec3 ourColor;

uniform float xColor;

void main()
{
	FragColor = vec4(xColor * ourColor.x, ourColor.y,  ourColor.z ,1.0f);
}