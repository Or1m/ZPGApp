#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

out vec3 fragPos;
out vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//uniform vec3 lightPosition;

uniform vec3 col;
out vec4 color;


void main () {
    color = vec4(col, 1.0);


    fragPos = vec3(modelMatrix * vec4(vp, 1.0));

    normal = inverse(transpose(mat3(modelMatrix))) * vn;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_colour;

in vec4 color; 

in vec3 fragPos;
in vec3 normal;


void main () {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(0.0, 0.0, 0.0) - fragPos);
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * vec3(1.0, 1.0, 1.0);
    vec3 result = (ambient + diffuse) * vec3(color);

    frag_colour = vec4(result, 1.0);
};