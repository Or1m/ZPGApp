#shader vertex
#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 tc;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 textureDir;

void main() {

    textureDir = vp;
    mat4 test = mat4(mat3(viewMatrix));

    gl_Position = (projectionMatrix * test * modelMatrix) * vec4(vp, 1.0);
};

#shader fragment
#version 400

out vec4 frag_color;

uniform vec3 color;
uniform samplerCube myTexture;
uniform int hasTexture;

in vec3 textureDir;


vec3 temp;

void main() {
    vec4 texColor = texture(myTexture, textureDir);

    if (hasTexture == 1)
        frag_color = vec4(color, 1.0) * texColor;
    else
        frag_color = vec4(color, 1.0);
};