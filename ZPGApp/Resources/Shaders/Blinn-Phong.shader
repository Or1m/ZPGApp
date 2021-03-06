#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 tc;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentPosition;
out vec3 normal;
out vec2 texCoord;

void main() {

    fragmentPosition = vec3(modelMatrix * vec4(vp, 1.0));
    normal = normalize(inverse(transpose(mat3(modelMatrix))) * vn);

    texCoord = tc;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
};

#shader fragment
#version 400

#define MAX_LIGHTS 4

vec3 calcDirForPointLight(inout float attenuation, int i);

out vec4 frag_color;

struct Light
{
    vec3 position;
    vec3 direction;
    vec3 color;

    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;

    int type;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 color;
uniform vec3 viewPosition;

uniform sampler2D myTexture;
uniform int hasTexture;

in vec2 texCoord;
in vec3 fragmentPosition;
in vec3 normal;

const float ambientStrength = 0.1;
const float specularStrength = 0.5;

void main() {
    float theta, attenuation = 1.0f;
    vec3 result = vec3(0.0, 0.0, 0.0);
    vec4 texColor = texture(myTexture, texCoord);

    for (int i = 0; i < numberOfLights; i++) {
        // ambient
        vec3 ambient = ambientStrength * lights[i].color;

        // diffuse
        vec3 lightDir;
        if (lights[i].type == 0 || lights[i].type == 2)
            lightDir = calcDirForPointLight(attenuation, i);

        if (lights[i].type == 1)
            lightDir = normalize(-lights[i].direction);

        if (lights[i].type == 2)
            theta = dot(lightDir, normalize(-lights[i].direction));

        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * lights[i].color;

        // specular
        vec3 specular;
        if (diffuseStrength == 0.0)
            specular = vec3(0.0, 0.0, 0.0);
        else {
            vec3 viewDir = normalize(viewPosition - fragmentPosition);
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
            specular = specularStrength * spec * lights[i].color;
        }

        if (lights[i].type == 0 || lights[i].type == 2) {
            ambient  *= attenuation;
            diffuse  *= attenuation;
            specular *= attenuation;
        }

        if (lights[i].type == 2 && theta < lights[i].cutOff)
            result += ambient * color;
        else
            result += (ambient + diffuse) * color + specular;
    }

    if (hasTexture == 1)
        frag_color = vec4(result, 1.0) * texColor;
    else
        frag_color = vec4(result, 1.0);
};

vec3 calcDirForPointLight(inout float attenuation, int i) {
    vec3 lightFrag = lights[i].position - fragmentPosition;
    float distance = length(lightFrag);

    attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

    return normalize(lightFrag);
}