#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform vec3 colors;
uniform bool isTexture;
uniform bool isTexture2;
uniform bool isColor;
uniform float alpha;

uniform sampler2D container_texture;
uniform sampler2D face_texture;
uniform sampler2D pyramid_texture;

void main()
{
	if(isTexture && isTexture2 && isColor)
			FragColor = mix(texture(container_texture,TexCoords), texture(face_texture, TexCoords), alpha) * vec4(colors,1.0f);
	else if (isTexture && isTexture2 && !isColor)
			FragColor = mix(texture(container_texture,TexCoords), texture(face_texture, TexCoords), alpha);
	else if (!isTexture && isTexture2 && isColor)
			FragColor = texture(face_texture, TexCoords) * vec4(colors,1.0f);
	else if(!isTexture && !isTexture2 && isColor)
			FragColor = vec4(colors,1.0f);
	else if(!isTexture && isTexture2 && !isColor)
			FragColor = texture(face_texture, TexCoords);
	else if(isTexture && !isTexture2 && isColor)
			FragColor = texture(container_texture, TexCoords) * vec4(colors,1.0f);
	else if(isTexture && !isTexture2 && !isColor)
			FragColor = texture(container_texture, TexCoords);
	else if(!isTexture && !isTexture2 && !isColor)
			FragColor = vec4(0.0f);

}