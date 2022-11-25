#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textCoord;

uniform mat4 uProjection;
uniform mat4 uModelView;

out vec2 vTextCoord;

void main()
{
	gl_Position = uProjection *  uModelView * vec4(position.x, position.y, 0.0f, 1.0f);
	vTextCoord = textCoord;
}