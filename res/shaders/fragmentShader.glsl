#version 430 core

in vec4 varyingColor;

out vec4 FragColor;

uniform mat4 mvp_matrix;

void main()
{
	FragColor = varyingColor;
};