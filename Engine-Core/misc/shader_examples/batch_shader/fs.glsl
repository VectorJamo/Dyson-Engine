#version 330 core

out vec4 uFragColor;

in vec2 vTextCoord;
in float vTextIndex;

uniform sampler2D uTextureUnits[32];

void main()
{
	int textIndex = int(vTextIndex);
	uFragColor = texture(uTextureUnits[textIndex], vTextCoord);
}