#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in float textIndex;

uniform mat4 uCameraTranslation;
uniform mat4 uCameraRotation;

uniform mat4 uProjection;

out vec2 vTextCoord;
out float vTextIndex;

void main()
{
	gl_Position = uProjection * uCameraTranslation * uCameraRotation * vec4(position.x, position.y, 0.0f, 1.0f);
	vTextCoord = textCoord;
	vTextIndex = textIndex;
}