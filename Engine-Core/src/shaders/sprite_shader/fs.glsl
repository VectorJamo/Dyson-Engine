#version 330 core

out vec4 uFragColor;

in vec2 vTextCoord;

uniform vec4 uColor;
uniform int uUseTexture;
uniform sampler2D uTextureUnit;

void main()
{
	if(uUseTexture == 1)
	{
		uFragColor = texture(uTextureUnit, vTextCoord);
	}else {
		uFragColor = uColor;
	}
}