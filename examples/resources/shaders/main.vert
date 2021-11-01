#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform float t;

out vec4 color;
out vec2 texCoords;

void main()
{
    color = vec4((aPos + 1)/2, 1.0) * (sin(6.28*t) + 1)/2;
    texCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
