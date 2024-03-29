#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;
uniform vec2 offsets[100];

void main()
{
	vec2 offset = offsets[gl_InstanceID];
    //gl_Position = vec4(aPos.xy + offset.xy, 0.0, 1.0);
	gl_Position = vec4(aPos.xy + aOffset + offset, 0.0, 1.0);
	//gl_Position = vec4(aPos.xy, 0.0, 1.0);
	fColor = aColor;
}