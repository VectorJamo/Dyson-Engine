#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 uTranslationToOrigin;
uniform mat4 uTranslationToOriginal;

uniform mat4 uRotation;

uniform mat4 uCameraTranslation;
uniform mat4 uCameraRotation;

uniform mat4 uProjection;

void main()
{
	gl_Position =  uProjection * uCameraTranslation * uTranslationToOriginal * uCameraRotation * uRotation * uTranslationToOrigin * vec4(position.x, position.y, 0.0f, 1.0f);
}