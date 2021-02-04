#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

uniform float opacity;

uniform vec4 color;

void main()
{
    vec4 texColor = texture(texture1, TexCoords);
	//FragColor =	vec4(vec3(1.0 - texture(texture1, TexCoords)), 1.0);

	//if(texColor.a < 0.1)
    //    discard;
	
	//texColor.a = texColor.a * opacity;

    FragColor = texColor * color;
}