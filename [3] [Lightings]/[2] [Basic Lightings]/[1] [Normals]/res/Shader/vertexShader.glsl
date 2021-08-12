#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{	
	normal = aNormal;
	TexCoords = aTexCoords;
	ourColor = aColor;
	gl_Position = projection * view * model * vec4(aPos , 1.0f);
}