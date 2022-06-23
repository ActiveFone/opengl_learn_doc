#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 P;

void main()
{
	TexCoords = aTexCoords;
	//vec3 ndcPos = P * aPos;
	//ndcPos = ndcPos * 2 - vec3(1.0, 1.0, 0.0);
    gl_Position = P * vec4(aPos, 1.0);

    //gl_Position = vec4(aPos, 1.0);
}