#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{
	
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

// Directional Light
struct DirLight{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};
// Point Light
struct PointLight{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;
};
// Spot Light
struct SpotLight{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;
uniform vec3 viewPos;

vec3 CalDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 CalPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir);
vec3 CalSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir);

void main()
{
	//Properties
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	// Directional Light 
	vec3 result = CalDirLight(dirLight, norm, viewDir);
	// Point Light 
	for(int i = 0; i < 4; i++)
		result += CalPointLight(pointLights[i], norm ,fragPos, viewDir);
	// Spot Light 
	result += CalSpotLight(spotLight,norm ,fragPos,viewDir);

	FragColor = vec4(result, 1.0f);

}

vec3 CalDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);


	return ambient + diffuse + specular;
}

vec3 CalPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragpos);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Attenuation
	float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));
	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	return ambient + diffuse + specular;
}

vec3 CalSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragpos);
	// Diffuse Shading
	float diff = max(dot(norm,lightDir),0.0f);
	// Specular Shading
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	// Attenuation
	float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));
	// Spotlight intensity
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0f,1.0f);

	// Combine results
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords);
	vec3 specular = light.specular * spec * texture(material.specular,TexCoords);

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;


	return ambient + diffuse + specular;
}
