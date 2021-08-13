#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
	ourColor = aColor;
	fragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = projection * view * model  * vec4(aPos, 1.0f);
}