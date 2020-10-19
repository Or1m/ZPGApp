#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 u_lightPosition;
uniform vec3 u_color;

out vec3 color;
out vec3 lightPosition;
out vec3 fragmentPosition;
out vec3 normal;

void main () {
    color = u_color;
    lightPosition = u_lightPosition;

    fragmentPosition = vec3(modelMatrix * vec4(vp, 1.0));
    normal = inverse(transpose(mat3(modelMatrix))) * vn;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_colour;

in vec3 color;
in vec3 lightPosition;

in vec3 fragmentPosition;
in vec3 normal;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main () {
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosition - fragmentPosition);
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;
    
    vec3 result = (ambient + diffuse) * color;
    frag_colour = vec4(result, 1.0);
};