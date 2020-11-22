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

#define MAX_LIGHTS 4
struct Light
{
    vec3 position;
    vec3 color;

    vec3 diffuse;
    vec3 specular;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 color;

in vec3 fragmentPosition;
in vec3 normal;

const float ambientStrength = 0.1;

void main() {
    vec3 result = vec3(0.0, 0.0, 0.0);

    // for all light sources
    for (int i = 0; i < numberOfLights; i++) {
        // ambient
        vec3 ambient = ambientStrength * lights[i].color;

        // diffuse
        vec3 lightDir = normalize(lights[i].position - fragmentPosition);
        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * lights[i].color;

        result += (ambient + diffuse) * color;
    }

    frag_color = vec4(result, 1.0);
};