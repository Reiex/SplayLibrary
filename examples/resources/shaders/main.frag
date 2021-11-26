#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 cameraPos;

void main()
{
    vec3 lightDir = normalize(vec3(-1.0, -1.0, -1.0));
    vec3 baseColor = vec3(0.7, 0.7, 0.7);

    float ambiant = 0.05;
    float diffuse = dot(-lightDir, normalize(normal));
    
    vec3 reflection = reflect(lightDir, normalize(normal));

    float specular = pow(clamp(dot(reflection, normalize(cameraPos - pos)), 0.0, 1.0), 100.0);

    FragColor = vec4(baseColor * (ambiant + diffuse + specular), 1.0);
} 
