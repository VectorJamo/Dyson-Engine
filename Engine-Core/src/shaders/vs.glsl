#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textCoord;

uniform mat4 uModelTranslation;
uniform mat4 uModelScale;
uniform mat4 uModelRotation;

uniform mat4 uCameraTranslation;
uniform mat4 uCameraRotation;

uniform mat4 uProjection;

out vec2 vTextCoord;

void main()
{
	mat4 scale = uModelScale;
	mat4 rotation = uModelRotation * uCameraRotation;
	mat4 translation = uModelTranslation * uCameraTranslation;

	gl_Position =  uProjection * translation * rotation * scale * vec4(position.x, position.y, 0.0f, 1.0f);
	vTextCoord = textCoord;
}