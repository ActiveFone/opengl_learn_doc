#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 Position;
uniform mat4 Rotate;
uniform mat4 Scale;

void main()
{
	TexCoords = aTexCoords;
    gl_Position = Rotate * Position * Scale * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
}