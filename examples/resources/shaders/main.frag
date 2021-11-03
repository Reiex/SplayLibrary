#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCoords;

uniform sampler2D colorTexture;

void main()
{
    FragColor = color * texture(colorTexture, texCoords);
} 
