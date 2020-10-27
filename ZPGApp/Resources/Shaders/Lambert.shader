#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentPosition;
out vec3 normal;

void main() {

    fragmentPosition = vec3(modelMatrix * vec4(vp, 1.0));
    normal = normalize(inverse(transpose(mat3(modelMatrix))) * vn);

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_color;

uniform vec3 color;
uniform vec3 lightPosition;
uniform vec3 lightColor;

in vec3 fragmentPosition;
in vec3 normal;

const float ambientStrength = 0.1;

void main() {
    // ambient
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 lightDir = normalize(lightPosition - fragmentPosition);
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    vec3 result = (ambient + diffuse) * color;

    frag_color = vec4(result, 1.0);
};