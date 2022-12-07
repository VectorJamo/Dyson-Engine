#version 330 core

out vec4 uFragColor;

in vec2 vTextCoord;

uniform vec4 uColor;
uniform sampler2D uTextureUnit;

void main()
{
	uFragColor = uColor * texture(uTextureUnit, vTextCoord);
}