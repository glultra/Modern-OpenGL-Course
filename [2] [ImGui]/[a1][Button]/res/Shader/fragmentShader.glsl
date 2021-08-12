#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform bool isTexture;
uniform bool isColor;

uniform vec3 colors;

uniform sampler2D container_texture;
uniform sampler2D face_texture;

uniform float alpha;

void main()
{
	if (isTexture && isColor)
		FragColor = mix(texture(container_texture, TexCoords), texture(face_texture, TexCoords), alpha) * vec4(colors,1.0f);
	else if(isTexture && !isColor)
		FragColor = mix(texture(container_texture, TexCoords), texture(face_texture, TexCoords), alpha);
	else if(!isTexture && isColor)
		FragColor = vec4(colors,1.0f);
	else
		FragColor = vec4(1.0f);
}