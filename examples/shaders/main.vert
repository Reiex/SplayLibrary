#version 330 core
layout (location = 0) in vec3 aPos;

uniform float t;

out vec4 color;

void main()
{
    color = vec4((aPos + 1)/2, 1.0) * (sin(6.28*t) + 1)/2;
    gl_Position = vec4(aPos, 1.0);
}
