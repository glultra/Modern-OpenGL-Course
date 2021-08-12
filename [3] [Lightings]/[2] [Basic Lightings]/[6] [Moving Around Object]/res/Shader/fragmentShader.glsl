#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float shininess;

void main()
{
	// Ambient
	float ambientStrength = 0.2f;
	vec3 ambient = lightColor * ambientStrength;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = lightColor * diff;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), shininess);
	vec3 specular = lightColor * spec * specularStrength;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result,1.0f);
}