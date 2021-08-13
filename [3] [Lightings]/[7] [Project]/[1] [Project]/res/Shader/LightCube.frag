#version 330 core

out vec4 FragColor;

struct Light
{
	vec3 ambient;
	vec3 diffuse;
};

uniform Light light;

void main()
{	
	vec3 result = light.ambient + light.diffuse; 
	FragColor = vec4(result, 1.0f);
}