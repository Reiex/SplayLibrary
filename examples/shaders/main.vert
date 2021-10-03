#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 color;

void main()
{
    color = vec4((aPos + 1)/2, 1.0);
    gl_Position = vec4(aPos, 1.0);
}
