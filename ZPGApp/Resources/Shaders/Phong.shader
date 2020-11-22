#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform vec3 color;
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
uniform vec3 viewPosition;

in vec3 fragmentPosition;
in vec3 normal;

const float ambientStrength = 0.1;
const float specularStrength = 0.5;

void main () {
    vec3 result = vec3(0.0, 0.0, 0.0);
    // for all light sources
    for (int i = 0; i < numberOfLights; i++) {
        // ambient
        vec3 ambient = ambientStrength * lights[i].color;

        // diffuse
        vec3 lightDir = normalize(lights[i].position - fragmentPosition);
        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * lights[i].color;

        // specular
        vec3 specular;
        if (diffuseStrength == 0.0)
            specular = vec3(0.0, 0.0, 0.0);
        else {
            vec3 viewDir = normalize(viewPosition - fragmentPosition);
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
            specular = specularStrength * spec * lights[i].color;
        }

        result += (ambient + diffuse) * color + specular;
        //vec3 result = (ambient + diffuse + specular) * color;
    }

    frag_color = vec4(result, 1.0);
};