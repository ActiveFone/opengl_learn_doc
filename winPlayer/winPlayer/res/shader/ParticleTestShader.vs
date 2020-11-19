#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 coord;

void main()
{
    TexCoords = aTexCoords;
    //gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 screenPos = (aPos) / 10;
	screenPos.xy = screenPos.xy + coord.xy;
	
    gl_Position = vec4(screenPos, 1.0);
}