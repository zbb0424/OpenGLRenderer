#version 430 core

layout(location = 0) out vec4 color;
 
uniform sampler2D texture0;
uniform sampler2D texture1;

in vec2 v_TexCoord;

void main()
{
	mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
};