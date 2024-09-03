#version 430 core

layout (location = 0) in vec3 aPos;

uniform mat4 mvp_matrix;

out vec4 varyingColor;

void main()
{
    gl_Position = mvp_matrix * vec4(aPos, 1.0);
    varyingColor = vec4(aPos,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}
