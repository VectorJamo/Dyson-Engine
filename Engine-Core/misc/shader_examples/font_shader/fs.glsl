#version 330 core

out vec4 uFragColor;

in vec2 vTextCoord;
in float vTextUnit;

uniform vec4 uColor;
uniform sampler2D uTextureUnits[32];

void main()
{
	int textureUnit = int(vTextUnit);

	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(uTextureUnits[textureUnit], vTextCoord).r);
	uFragColor = uColor * sampled;
}