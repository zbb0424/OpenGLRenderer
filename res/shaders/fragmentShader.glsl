#version 430 core

layout(location = 0) out vec4 color;
 
in vec2 v_TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	color = mix(texture(texture0, v_TexCoord), texture(texture1, v_TexCoord), 0.8);
};

