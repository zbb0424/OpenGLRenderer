#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;
	FragPos = vec3(model * position);
	v_TexCoord = texCoord;
	Normal = mat3(transpose(inverse(model))) * normal;
};