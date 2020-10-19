#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentPosition;
out vec3 normal;

void main () {

    fragmentPosition = vec3(modelMatrix * vec4(vp, 1.0));
    normal = inverse(transpose(mat3(modelMatrix))) * vn;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_colour;

uniform vec3 color;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

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

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * color;
    frag_colour = vec4(result, 1.0);
};